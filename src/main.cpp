import std;
import vector_module;

int main() {
  try {
    std::println("--- 1. Testing Core Vector Functionality ---");

    Vector<double> vec_a(3, -5.0, 5.0);
    Vector<double> vec_b(3, -5.0, 5.0);

    std::println("Random Vector A: {}", vec_a);
    std::println("Random Vector B: {}", vec_b);

    std::println("A + B: {}", (vec_a + vec_b));
    std::println("A - B: {}", (vec_a - vec_b));
    std::println("A * 2.0 (Scalar): {}", (vec_a * 2.0));
    std::println("2.0 * B (Commutative): {}", (2.0 * vec_b));
    std::println("A / 2.0: {}", (vec_a / 2.0));
    std::println("Dot Product (A * B): {}", (vec_a * vec_b));

    std::println("\n--- 2. Specialized Complex Dot Product ---");
    Vector<std::complex<double>> comp_a(2, 0.0, 2.0);
    Vector<std::complex<double>> comp_b(2, 0.0, 2.0);
    std::println("Complex A: {}", comp_a);
    std::println("Complex B: {}", comp_b);
    std::println("Complex Dot Product (with conjugation): {}", (comp_a * comp_b));

    std::println("\n--- 3. Geometric Tasks Execution ---");

    double area = calculate_triangle_area(vec_a, vec_b);
    std::println("Task 1 (Triangle Area): {}", area);

    auto bisector = find_bisector_vector(vec_a, vec_b);
    std::println("Task 2 (Bisector Vector): {}", bisector);

    auto [angle1, angle2] = calculate_parallelogram_angles(vec_a, vec_b);
    std::println("Task 3 (Angles in Rad): {} and {} (Sum: {})", angle1, angle2, (angle1 + angle2));

    auto perp = find_any_perpendicular_unit(vec_a);
    std::println("Task 4 (Perpendicular Unit to A): {}", perp);

    std::println("\n--- 4. Error Handling Test ---");
    Vector<double> wrong_dim(4, 1.0);
    std::println("Attempting to add different dimensions:");
    auto crash = vec_a + wrong_dim; 

  } catch (const std::exception& ex) {
    std::println("Caught expected exception: {}", ex.what());
  }

  return 0;
}
