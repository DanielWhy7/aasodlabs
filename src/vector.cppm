module;
export module vector_module;
import std;

using std::size_t;

export template <typename T>
class Vector {
  size_t m_size;
  T* m_data;
  static constexpr double EPSILON = 1e-7;

  bool is_equal(const T& lhs, const T& rhs) const {
    if constexpr (requires { std::abs(lhs - rhs); }) return std::abs(lhs - rhs) < EPSILON;
    else if constexpr (requires { lhs.real(); }) return std::abs(lhs.real() - rhs.real()) < EPSILON && std::abs(lhs.imag() - rhs.imag()) < EPSILON;
    else return lhs == rhs;
  }
public:
  Vector(size_t size, T value) : m_size(size), m_data(new T[size]) {
    for (size_t i = 0; i < m_size; ++i) m_data[i] = value;
  }
  Vector(size_t size, double lower, double upper) : m_size(size), m_data(new T[size]) {
    std::random_device rd; std::mt19937 gen(rd());
    if constexpr (std::is_integral_v<T>) {
      std::uniform_int_distribution<T> dist(static_cast<T>(lower), static_cast<T>(upper));
      for (size_t i = 0; i < m_size; ++i) m_data[i] = dist(gen);
    } else if constexpr (std::is_floating_point_v<T>) {
      std::uniform_real_distribution<T> dist(static_cast<T>(lower), static_cast<T>(upper));
      for (size_t i = 0; i < m_size; ++i) m_data[i] = dist(gen);
    } else {
      using PartType = typename T::value_type;
      std::uniform_real_distribution<PartType> dist(static_cast<PartType>(lower), static_cast<PartType>(upper));
      for (size_t i = 0; i < m_size; ++i) m_data[i] = T(dist(gen), dist(gen));
    }
  }
  Vector(const Vector& other) : m_size(other.m_size), m_data(new T[other.m_size]) {
    for (size_t i = 0; i < m_size; ++i) m_data[i] = other.m_data[i];
  }
  Vector& operator=(const Vector& other) {
    if (this != &other) {
      T* new_data = new T[other.m_size];
      for (size_t i = 0; i < other.m_size; ++i) new_data[i] = other.m_data[i];
      delete[] m_data; m_data = new_data; m_size = other.m_size;
    }
    return *this;
  }
  ~Vector() { delete[] m_data; }
  [[nodiscard]] size_t size() const noexcept { return m_size; }
  
  T& operator[](size_t index) {
    if (index >= m_size) throw std::out_of_range("Out of bounds.");
    return m_data[index];
  }
  const T& operator[](size_t index) const {
    if (index >= m_size) throw std::out_of_range("Out of bounds.");
    return m_data[index];
  }
  Vector operator+(const Vector& other) const {
    if (m_size != other.m_size) throw std::invalid_argument("Size mismatch.");
    Vector r(m_size, T{});
    for (size_t i = 0; i < m_size; ++i) r.m_data[i] = m_data[i] + other.m_data[i];
    return r;
  }
  Vector operator-(const Vector& other) const {
    if (m_size != other.m_size) throw std::invalid_argument("Size mismatch.");
    Vector r(m_size, T{});
    for (size_t i = 0; i < m_size; ++i) r.m_data[i] = m_data[i] - other.m_data[i];
    return r;
  }
  T operator*(const Vector& other) const {
    if (m_size != other.m_size) throw std::invalid_argument("Size mismatch.");
    T r{};
    for (size_t i = 0; i < m_size; ++i) r += m_data[i] * other.m_data[i];
    return r;
  }
  Vector operator*(const T& scalar) const {
    Vector r(m_size, T{});
    for (size_t i = 0; i < m_size; ++i) r.m_data[i] = m_data[i] * scalar;
    return r;
  }
  Vector operator/(const T& scalar) const {
    if (is_equal(scalar, T{})) throw std::invalid_argument("Divide by zero.");
    Vector r(m_size, T{});
    for (size_t i = 0; i < m_size; ++i) r.m_data[i] = m_data[i] / scalar;
    return r;
  }
  bool operator==(const Vector& other) const {
    if (m_size != other.m_size) return false;
    for (size_t i = 0; i < m_size; ++i) if (!is_equal(m_data[i], other.m_data[i])) return false;
    return true;
  }
  bool operator!=(const Vector& other) const { return !(*this == other); }
  friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
    os << "[";
    for (size_t i = 0; i < vec.m_size; ++i) { os << vec.m_data[i]; if (i + 1 < vec.m_size) os << ", "; }
    return os << "]";
  }
};

export template <typename T>
Vector<T> operator*(const T& scalar, const Vector<T>& vec) { return vec * scalar; }

template <>
std::complex<double> Vector<std::complex<double>>::operator*(const Vector<std::complex<double>>& other) const {
  if (m_size != other.m_size) throw std::invalid_argument("Size mismatch.");
  std::complex<double> r{};
  for (size_t i = 0; i < m_size; ++i) r += m_data[i] * std::conj(other.m_data[i]);
  return r;
}

template <>
std::complex<float> Vector<std::complex<float>>::operator*(const Vector<std::complex<float>>& other) const {
  if (m_size != other.m_size) throw std::invalid_argument("Size mismatch.");
  std::complex<float> r{};
  for (size_t i = 0; i < m_size; ++i) r += m_data[i] * std::conj(other.m_data[i]);
  return r;
}

template <typename T>
double length(const Vector<T>& v) {
  double s = 0.0;
  for (size_t i = 0; i < v.size(); ++i) {
    if constexpr (requires { v[i].real(); }) s += std::norm(v[i]);
    else s += static_cast<double>(v[i] * v[i]);
  }
  return std::sqrt(s);
}

export template <typename T>
double calculate_triangle_area(const Vector<T>& a, const Vector<T>& b) {
  double la = length(a), lb = length(b), dot = 0.0;
  if constexpr (requires { (a * b).real(); }) dot = (a * b).real();
  else dot = static_cast<double>(a * b);
  double base = (la * la) * (lb * lb) - (dot * dot);
  return 0.5 * std::sqrt(base < 0.0 ? 0.0 : base);
}

export template <typename T>
Vector<double> find_bisector_vector(const Vector<T>& a, const Vector<T>& b) {
  double la = length(a), lb = length(b);
  if (la < 1e-9 || lb < 1e-9) throw std::invalid_argument("Zero length.");
  Vector<double> ua(a.size(), 0.0), ub(b.size(), 0.0);
  for (size_t i = 0; i < a.size(); ++i) {
    if constexpr (requires { a[i].real(); }) { ua[i] = a[i].real() / la; ub[i] = b[i].real() / lb; }
    else { ua[i] = static_cast<double>(a[i]) / la; ub[i] = static_cast<double>(b[i]) / lb; }
  }
  return ua + ub;
}

export template <typename T>
std::pair<double, double> calculate_parallelogram_angles(const Vector<T>& a, const Vector<T>& b) {
  double la = length(a), lb = length(b);
  if (la < 1e-9 || lb < 1e-9) throw std::invalid_argument("Zero length.");
  double dot = 0.0;
  if constexpr (requires { (a * b).real(); }) dot = (a * b).real();
  else dot = static_cast<double>(a * b);
  double cos_a = dot / (la * lb);
  if (cos_a > 1.0) cos_a = 1.0; 
  if (cos_a < -1.0) cos_a = -1.0;
  double alpha = std::acos(cos_a);
  return {alpha, std::numbers::pi - alpha};
}

export template <typename T>
Vector<double> find_any_perpendicular_unit(const Vector<T>& a) {
  size_t n = a.size();
  if (n < 2) throw std::invalid_argument("Need >= 2 dims.");
  Vector<double> perp(n, 0.0); size_t idx = n;
  for (size_t i = 0; i < n; ++i) {
    double val = 0.0;
    if constexpr (requires { a[i].real(); }) val = a[i].real();
    else val = static_cast<double>(a[i]);
    if (std::abs(val) > 1e-9) { idx = i; break; }
  }
  if (idx == n) throw std::invalid_argument("Zero vector.");
  size_t next = (idx + 1) % n;
  double vc = 0.0, vn = 0.0;
  if constexpr (requires { a[0].real(); }) { vc = a[idx].real(); vn = a[next].real(); }
  else { vc = static_cast<double>(a[idx]); vn = static_cast<double>(a[next]); }
  perp[idx] = -vn; perp[next] = vc;
  return perp / length(perp);
}

export template <typename T>
struct std::formatter<Vector<T>> : std::formatter<std::string> {
  auto format(const Vector<T>& v, std::format_context& ctx) const {
    std::string r = "[";
    for (size_t i = 0; i < v.size(); ++i) {
      if constexpr (requires { v[i].real(); }) r += std::format("({}+{}i)", v[i].real(), v[i].imag());
      else r += std::format("{}", v[i]);
      if (i + 1 < v.size()) r += ", ";
    }
    return std::formatter<std::string>::format(r + "]", ctx);
  }
};

export template <typename T>
struct std::formatter<std::complex<T>> : std::formatter<std::string> {
  auto format(const std::complex<T>& c, std::format_context& ctx) const {
    return std::formatter<std::string>::format(std::format("({}+{}i)", c.real(), c.imag()), ctx);
  }
};
