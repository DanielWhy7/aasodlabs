````markdown
# 実験レポート №2 — 連結リスト (バリアント 1, C++26)

| パラメータ       | 値                                                             |
|------------------|----------------------------------------------------------------|
| リストの種類     | **3** — 単方向循環連結リスト                                   |
| 基本課題         | **8** — 2つの整列済みリストを重複なしで統合する                |
| 発展課題         | **3** — 3つ（または2つ）のリストを用いたハノイの塔            |
| 言語             | **C++26**（モジュール、コントラクト、`import std;`）           |
| ビルドシステム   | **CMake 4.1+** と Ninja、GCC / Clang / MSVC 用プリセット       |

---

## 概要

本プロジェクトは、単方向**循環**連結リストに基づくテンプレートクラス
`linked_list<T>` と、補助構造体 `node<T>` を実装します。このクラスは
動的に割り当てたノードを所有し（rule of three）、完全にコピー可能で、
不正な引数に対して `std::stdexcept` 由来の例外を送出します。

このクラスの上に、2つの実践的な課題を解きます：

* **(基本)** 2つの整列済みリストを、重複を含まない1つの整列済みリストに
  統合する；
* **(発展)** ハノイの塔。各棒はリストで表現され、棒の状態は ASCII の
  塔として出力される。

コードは **K&R スタイル**（`型 名前() {`、2スペースインデント、
`snake_case` 識別子）で書かれており、cppreference に記載されている
**C++26 の機能**を使用しています：

* **名前付きモジュール** — `import std;` により、ヘッダーファイルなしで
  標準ライブラリ全体をスコープに導入できる；
* **コントラクト** — `contract_assert`（および宣言子形式の `pre` /
  `post`）は、`tail_->next == head_` や `size_ == expected` といった
  内部不変条件を表現する。ユーザー向けのエラーは引き続き例外を用いる
  ため、呼び出し側は回復できる。

## リポジトリ構成

```
.
├── CMakeLists.txt
├── CMakePresets.json
├── .gitignore
├── README.md
├── LICENSE                       # GPLv3
└── src/
    ├── linked_list.cppm          # linked_list<T> と node<T>        (モジュールインターフェース)
    ├── tasks.cppm                # tasks モジュール                 (モジュールインターフェース)
    ├── tasks.cpp                 # tasks モジュール                 (実装)
    ├── main.cpp                  # ▶ 対話型プログラム — main() を持つ
    └── test.cpp                  # ▶ 自動テストスイート — main() を持つ
```

`main.cpp` と `test.cpp` はそれぞれ独自の `main()` を定義しており、
2つのモジュールを含む静的ライブラリ `lablib` を共有する
**2つの独立した実行ファイル**（`main` と `tests`）にコンパイルされます。

## 要件

本作業は課題の最低要件に従います：

1. 最高レベルの警告で警告なしにコンパイルされる：
   * GCC / Clang: `-Wall -Wconversion -Wextra -Wpedantic`
   * MSVC: `/W4 /utf-8`
2. グローバル変数を使用しない（定数は許可）。
3. すべての識別子は英語で記述する。翻字は禁止。ロシア語はコメント内
   でのみ使用可。
4. 行ごとのコメントは禁止 — 論理ブロックごとに短いコメントを最大1つ
   まで。
5. 単一の一貫した命名スタイル（K&R / `snake_case`）を、**すべての**
   名前付き実体 — 関数、メソッド、クラス、変数、パラメータ、ファイル —
   に適用する。
6. Git リポジトリには、説明的なメッセージを持つ意味のある一連の
   コミットと、適切に設定された `.gitignore` が含まれる。ビルド成果物は
   決してコミットしない。

課題からの追加制約：

* **STL コンテナは一切使用しない**（`std::vector`、`std::list` などは
  禁止）。
* クラスはコピー可能で、割り当てたリソースを直接管理する。
* 不正な状況（空リストに対する `operator[]`、空リストに対する
  `pop_head` / `pop_tail` など）では `<stdexcept>` 由来の例外を送出する。
* 入出力はすべて `std::cin` / `std::cout` を介してのみ行う。
* 課題の解法はクラスの**外**に置く — `tasks` モジュール内の自由関数で
  ある。

## ビルド

### CMake を使用する場合（推奨）

```sh
cmake -G Ninja -B build -Wno-dev
cmake --build build
```

ビルドにより `/build` 以下に2つの実行ファイルが生成されます：

| バイナリ | 用途 |
|----------|------|
| `main`   | 対話型プログラム — 課題8、次に課題3を実行 |
| `tests`  | 自動テストスイート（17テスト）。成功時は `0` で終了 |

### コンパイラを直接使用する場合（GCC 16.1+）

```sh
g++ -std=c++26 -fmodules -fcontracts \
    -Wall -Wconversion -Wextra -Wpedantic \
    --compile-std-module \
    src/main.cpp src/tasks.cpp -o main
g++ -std=c++26 -fmodules -fcontracts \
    -Wall -Wconversion -Wextra -Wpedantic \
    --compile-std-module \
    src/test.cpp src/tasks.cpp -o tests
```

`-fcontracts` は `linked_list` と `tasks.cpp` で使用される C++26 の
コントラクトアサーションを有効にします。

## 実行

```sh
# 1) まず自動テストスイート
./build/linux-debug/tests
# 2) 次に対話型プログラム
./build/linux-debug/main
```

### テストスイートの出力

```
=== Automated tests ===
  PASS: default constructor
  PASS: random fill constructor
  PASS: push_tail / push_head
  PASS: modulo indexing
  PASS: empty index throws
  PASS: copy constructor
  PASS: assignment
  PASS: pop_head
  PASS: pop_tail
  PASS: delete_node
  PASS: push_tail(list)
  PASS: push_head(list)
  PASS: merge_sorted_unique
  PASS: merge with empty
  PASS: merge both empty
  PASS: merge collapses duplicates
  PASS: hanoi(0) is a no-op
=== All tests passed ===
```

### 対話セッション

```
Task 8: merging two sorted lists without duplicates
Enter first list (count then values): 4 1 3 5 7
Enter second list (count then values): 5 2 3 4 5 8
Merged: [1, 2, 3, 4, 5, 7, 8]

Task 3: Tower of Hanoi
Enter number of disks: 3

Initial state:
A            B            C
============================
[1]          [ ]          [ ]
[2]          [ ]          [ ]
[3]          [ ]          [ ]

Move 1: A -> C
...
Total moves: 7
```

## `linked_list<T>` の API

| メンバー                                        | 説明                                                                 |
|-------------------------------------------------|----------------------------------------------------------------------|
| `linked_list()`                                 | デフォルトコンストラクタ — 空リスト。                                |
| `linked_list(const linked_list&)`               | コピーコンストラクタ（深いコピー）。                                 |
| `linked_list(std::size_t, seed, min, max)`      | ランダム値で埋めるコンストラクタ（`requires std::integral<T>`）。    |
| `~linked_list()`                                | すべてのノードを解放する。                                           |
| `operator=`                                     | コピー代入（copy-and-swap）。                                        |
| `swap(linked_list&)`                            | O(1) のメンバー swap。                                               |
| `size()` / `empty()`                            | サイズ問い合わせ。                                                   |
| `push_tail(const T&)`                           | 末尾に1要素を追加する。                                              |
| `push_tail(const linked_list&)`                 | 末尾に別のリストを追加する。                                         |
| `push_head(const T&)`                           | 先頭に1要素を追加する。                                              |
| `push_head(const linked_list&)`                 | 先頭に別のリストを追加する。                                         |
| `pop_head()`                                    | 先頭要素を削除する。空の場合は例外を送出。                           |
| `pop_tail()`                                    | 末尾要素を削除する。空の場合は例外を送出。                           |
| `delete_node(const T&)`                         | 値が引数と等しいすべてのノードを削除する。                           |
| `operator[](std::size_t)`                       | 要素アクセス。インデックスは**サイズで剰余**を取る（循環リスト）。   |
| `operator[](std::size_t) const`                 | 同上、読み取り専用。                                                 |
| `operator<<`                                    | リストを `std::ostream` に出力する（`std::cout` で使用）。           |

リストは循環しているため、任意のインデックスは現在のサイズで剰余を
取られ、どのインデックスも有効な要素を返します。空のリストの場合は
依然として `std::out_of_range` を送出します。

## 基本課題 8 — 重複なしで整列済みリストを統合する

```cpp
linked_list<int> merge_sorted_unique(const linked_list<int>& first,
                                     const linked_list<int>& second);
```

両入力は昇順に整列済みであると仮定します。この関数は線形な
**2ポインタマージ**を行い、等しい隣接要素をスキップして、どちらの
入力からも各異なる値がちょうど1回だけ含まれる新しい整列済みリストを
返します。単一入力**内**の重複も同様にまとめられます。

計算量：時間 `O(n + m)`、追加ノード `O(n + m)`。

## 発展課題 3 — リストを用いたハノイの塔

```cpp
void hanoi(unsigned int disk_count);
```

3つの `linked_list<unsigned>` インスタンスが棒 `A`、`B`、`C` を表します。
円盤はそのサイズとして格納される（大きい値 = 大きい円盤）ため、各棒は
降順に整列されたリストであり、最小の円盤は常にその**先頭**にあります。
これにより、ハノイでは最上位（最小）の円盤しか移動できないため、合法な
移動は移動元の棒での `pop_head` + 移動先の棒での `push_head` となります。

再帰的解法は `n` 個の円盤を `A` から `C` へ、`B` を補助棒として移動
します。各移動の後、3つの棒すべての状態が ASCII の塔として出力されます
（例：サイズ3の円盤は `[3]`、空きスロットは `[ ]`）。棒は下揃えで描画
されるため、円盤は常に台座に「乗っている」ように見えます。

再帰的解法は `2^n - 1` 回の移動で完了します。

## 使用している C++26 の機能

| 機能 | 場所 | 目的 |
|------|------|------|
| **名前付きモジュール**（`import std;`） | `linked_list.cppm`、`tasks.cppm`、`tasks.cpp`、`main.cpp`、`test.cpp` | プリプロセッサヘッダーなしで、より高速でクリーンなコンパイル。 |
| **コントラクト**（`contract_assert`） | `linked_list` のメンバー関数 | デバッグビルドで内部不変条件（`tail_->next == head_`、`size_ == other.size_` など）を検証する。 |
| **`requires` 節** | `linked_list(count, seed, min, max)` | ランダム値コンストラクタを整数型に制限する。 |
| **標準ライブラリモジュール** | `import std;` | `#include` なしで標準ライブラリ全体が利用可能。 |

> **注：** パターンマッチングは **C++26 には含まれず**、C++29 に延期
> されました。したがって本プロジェクトでは `std::match` を使用しません。

## モジュール構成（なぜ `tasks.cppm` + `tasks.cpp` なのか？）

`tasks` は **モジュールインターフェースユニット**（`tasks.cppm`、2つの
エクスポート関数を宣言）と **モジュール実装ユニット**（`tasks.cpp`、
その本体を定義）に分割されています。これはヘッダーと `.cpp` の分割の
モジュール時代における等価物です：

* `hanoi` や `merge_sorted_unique` の本体を編集しても、再コンパイル
  されるのは `tasks.cpp` のみで、**`main.cpp` や `test.cpp` は再コンパイル
  されない**。
* ファイルローカルなヘルパー（`print_disk_field`、`print_rod_cell`、
  `print_state`、`hanoi_recursive`）は `tasks.cpp` 内に `static` 関数と
  して存在し、モジュールの利用者からは見えない。

`linked_list` は同じようには分割されていません。これはテンプレートで
あるため、その完全な定義をインスタンス化するすべての翻訳単位から見える
必要があるからです。したがってすべてが `linked_list.cppm` にあります。

## コーディングスタイル

K&R / Linux カーネル風：

* クラス、構造体、関数、変数、パラメータ、ファイル：`snake_case`
  （`linked_list`、`node`、`push_tail`、`merge_sorted_unique`）。
* **戻り値の型と関数名を同じ行に**、開き波括弧も同じ行に置く：

  ```cpp
  int main() {
    ...
  }
  ```

* 2スペースインデント。
* `NULL` の代わりに `nullptr`、C キャストの代わりに `static_cast<>`。
* 関数名と `(` の間にスペースを入れない。

このスタイルはプロジェクト内のすべての名前付き実体に一様に適用されます。
````
