# Cyclic Code Calculator GF(2)

## 1. Giới thiệu

Đây là project xây dựng công cụ tính toán một số thông tin cơ bản của mã cyclic trên trường nhị phân GF(2).

Với dữ liệu đầu vào gồm độ dài mã `n`, số bit thông tin `k` và đa thức kiểm tra `h(x)`, chương trình sẽ tính ra đa thức sinh `g(x)`, khoảng cách mã tối thiểu, số lỗi phát hiện được và số lỗi sửa được.

Ngoài bản chạy bằng C++ trên terminal, nhóm có xây dựng thêm giao diện web bằng file `index.html` để việc nhập dữ liệu và xem kết quả trực quan hơn. Giao diện web có thể sinh lời giải tự luận, sinh câu hỏi trắc nghiệm và xuất mã LaTeX để đưa sang Overleaf.

Link GitHub project:

```text
https://github.com/vanduc-sec/cyclic-code
```

---

## 2. Thành viên nhóm

| STT | Họ và tên | Mã sinh viên |
|---|---|---|
| 1 | Lê Anh Mỹ | B24DCAT200 |
| 2 | Cao Văn Đức | B24DCAT058 |
| 3 | Phạm Vũ Đức Duy | B24DCAT081 |

Bạn đại diện nộp bài: **Cao Văn Đức - B24DCAT058**

---

## 3. Bài toán xử lý

Chương trình làm việc với mã cyclic tuyến tính \( C(n, k) \) trên GF(2).

Input có dạng:

```text
n k
h(x)
```

Trong đó:

- `n` là độ dài từ mã.
- `k` là số bit thông tin.
- `h(x)` là đa thức kiểm tra, được nhập dưới dạng chuỗi nhị phân.

Ví dụ:

```text
7 3
1011
```

Chuỗi `1011` tương ứng với đa thức:

\[
h(x) = x^3 + x + 1
\]

Từ đa thức kiểm tra \( h(x) \), chương trình tính đa thức sinh:

\[
g(x) = \frac{x^n + 1}{h(x)}
\]

Sau đó chương trình sinh các từ mã khác 0, tính trọng số Hamming của từng từ mã và tìm trọng số nhỏ nhất để xác định khoảng cách mã tối thiểu \( d_{min} \).

Từ \( d_{min} \), chương trình tính được:

\[
\text{số lỗi phát hiện được} = d_{min} - 1
\]

\[
\text{số lỗi sửa được} = \left\lfloor \frac{d_{min} - 1}{2} \right\rfloor
\]

---

## 4. Cấu trúc project

Project gồm các file chính sau:

```text
cyclic-code/
├── main.cpp
├── index.html
├── README.md
└── tests/
    ├── test01.in
    ├── test01.out
    ├── test02.in
    ├── test02.out
    ├── test03.in
    ├── test03.out
    ├── test04.in
    ├── test04.out
    ├── test05.in
    └── test05.out
```

Trong đó:

| File/thư mục | Mô tả |
|---|---|
| `main.cpp` | Chương trình C++ chính, chạy trên terminal |
| `index.html` | Giao diện web để nhập dữ liệu và xem kết quả |
| `README.md` | Tài liệu mô tả và hướng dẫn sử dụng project |
| `tests/` | Các bộ test mẫu để kiểm tra chương trình |

---

## 5. Thiết kế chương trình

Project được chia thành hai phần: phần xử lý bằng C++ và phần giao diện web.

### 5.1. Phần C++ trong `main.cpp`

File `main.cpp` là chương trình chính dùng để xử lý thuật toán.

Các công việc chính của chương trình:

- Đọc input gồm `n`, `k` và chuỗi nhị phân biểu diễn `h(x)`.
- Chuyển chuỗi nhị phân thành dạng đa thức.
- Thực hiện các phép toán đa thức trên GF(2).
- Tính \( x^n + 1 \).
- Chia \( x^n + 1 \) cho \( h(x) \) để tìm \( g(x) \).
- Kiểm tra trường hợp input không hợp lệ.
- Sinh toàn bộ thông điệp khác 0 có độ dài `k`.
- Tạo các từ mã tương ứng.
- Tính trọng số Hamming.
- Tìm khoảng cách mã tối thiểu.
- In kết quả ra màn hình.

Phần C++ được dùng để kiểm tra thuật toán lõi của project.

### 5.2. Phần giao diện web trong `index.html`

File `index.html` là bản giao diện web giúp người dùng thao tác dễ hơn.

Các chức năng chính:

- Nhập input chuẩn giống chương trình C++.
- Nhập riêng từng giá trị `n`, `k`, `h(x)` nếu muốn.
- Chọn dạng kết quả:
  - Lời giải tự luận.
  - Câu hỏi trắc nghiệm.
- Hiển thị các bước tính toán.
- Hiển thị đáp án cuối cùng.
- Copy output dạng text.
- Copy mã LaTeX để dán sang Overleaf.

File này chạy trực tiếp trên trình duyệt, không cần cài thêm thư viện.

---

## 6. Công nghệ sử dụng

Project sử dụng:

- C++17 cho chương trình chạy terminal.
- HTML, CSS, JavaScript cho giao diện web.
- LaTeX/Overleaf để trình bày lời giải và câu hỏi trắc nghiệm.

Project không dùng thư viện ngoài, không cần cài package bằng `npm`, `pip` hay công cụ tương tự.

---

## 7. Cài đặt và thiết lập môi trường

### 7.1. Yêu cầu để chạy chương trình C++

Máy cần có trình biên dịch C++ hỗ trợ C++17.

Có thể dùng:

- Windows: MinGW g++ hoặc MSYS2 g++.
- Linux: GCC/g++.
- macOS: clang++ hoặc g++.

Kiểm tra máy đã có g++ chưa:

```bash
g++ --version
```

Nếu lệnh trên hiện ra phiên bản g++ thì có thể biên dịch chương trình.

### 7.2. Cài g++ nếu chưa có

Trên Ubuntu/Debian:

```bash
sudo apt update
sudo apt install g++
```

Trên macOS:

```bash
xcode-select --install
```

Trên Windows, có thể cài MinGW hoặc MSYS2, sau đó thêm đường dẫn `g++` vào biến môi trường `PATH`.

### 7.3. Tải project về máy

Có thể clone project bằng Git:

```bash
git clone https://github.com/vanduc-sec/cyclic-code.git
cd cyclic-code
```

Hoặc tải file `.zip` từ GitHub rồi giải nén.

---

## 9. Chạy chương trình C++

### Trên Linux/macOS

```bash
./main
```

### Trên Windows PowerShell

```powershell
.\main.exe
```

Sau đó nhập input theo dạng:

```text
n k
h(x)
```

Ví dụ:

```text
7 3
1011
```

---

## 10. Chạy chương trình với file test

Trong thư mục `tests/` có các file test mẫu.

Ví dụ chạy test đầu tiên trên Linux/macOS:

```bash
./main < tests/test01.in
```

Trên Windows PowerShell:

```powershell
.\main.exe < tests\test01.in
```

Có thể chạy các test khác tương tự:

```bash
./main < tests/test02.in
./main < tests/test03.in
./main < tests/test04.in
./main < tests/test05.in
```

Kết quả in ra có thể đối chiếu với các file `.out` tương ứng trong thư mục `tests/`.

---

## 11. Chạy giao diện web

Giao diện web nằm trong file:

```text
index.html
```

Cách chạy:

1. Mở thư mục project.
2. Nháy đúp vào file `index.html`.
3. File sẽ mở bằng trình duyệt như Chrome, Edge hoặc Firefox.
4. Nhập input chuẩn, ví dụ:

```text
7 3
1011
```

5. Bấm nút tính kết quả.
6. Chọn dạng kết quả cần xem:
   - `Tự luận`: xem lời giải từng bước.
   - `Trắc nghiệm`: xem câu hỏi trắc nghiệm và đáp án.

Giao diện web có thể chạy offline, không cần server và không cần cài thêm thư viện.

---

## 12. Xuất LaTeX sang Overleaf

Trong giao diện web có nút copy mã LaTeX.

Cách sử dụng:

1. Mở `index.html`.
2. Nhập input.
3. Bấm tính kết quả.
4. Bấm nút `Chép LaTeX`.
5. Mở Overleaf.
6. Tạo project mới.
7. Dán nội dung vừa copy vào file `.tex`.
8. Compile để xem kết quả.

Nội dung LaTeX gồm phần lời giải tự luận, câu hỏi trắc nghiệm và đáp án.

---

## 13. Kiểm tra tính đúng đắn

Có thể kiểm tra project theo hai cách: kiểm tra bằng chương trình C++ và kiểm tra bằng giao diện web.

### 13.1. Kiểm tra bằng C++

Biên dịch chương trình:

```bash
g++ -std=c++17 main.cpp -o main
```

Chạy với test mẫu:

```bash
./main < tests/test01.in
```

Trên Windows:

```powershell
.\main.exe < tests\test01.in
```

Sau đó so sánh kết quả in ra với file:

```text
tests/test01.out
```

Nếu kết quả trùng hoặc tương đương về mặt toán học thì chương trình chạy đúng với test đó.

Có thể kiểm tra tiếp các test còn lại:

```bash
./main < tests/test02.in
./main < tests/test03.in
./main < tests/test04.in
./main < tests/test05.in
```

### 13.2. Kiểm tra bằng giao diện web

Mở file `index.html`, nhập cùng input với file test.

Ví dụ:

```text
7 3
1011
```

Sau đó kiểm tra các thông tin trên giao diện:

- Đa thức kiểm tra \( h(x) \).
- Đa thức sinh \( g(x) \).
- Khoảng cách mã tối thiểu \( d_{min} \).
- Số lỗi phát hiện được.
- Số lỗi sửa được.
- Từ mã có trọng số nhỏ nhất.
- Phần lời giải tự luận.
- Phần câu hỏi trắc nghiệm và đáp án.

---

## 14. Ví dụ minh họa

Input:

```text
7 3
1011
```

Với input này:

\[
n = 7,\quad k = 3
\]

\[
h(x) = x^3 + x + 1
\]

Chương trình sẽ tính:

\[
g(x) = \frac{x^7 + 1}{h(x)}
\]

Sau khi có \( g(x) \), chương trình sinh các từ mã từ các thông điệp khác 0, tính trọng số Hamming của từng từ mã và lấy trọng số nhỏ nhất để tìm \( d_{min} \).

Từ đó chương trình suy ra số lỗi phát hiện được và số lỗi sửa được của mã.

---

## 16. Ghi chú

Project có hai cách sử dụng:

- Dùng `main.cpp` để chạy nhanh trên terminal và kiểm tra thuật toán.
- Dùng `index.html` để xem kết quả trực quan hơn, có lời giải tự luận, câu hỏi trắc nghiệm và xuất LaTeX.

Nhờ đó project vừa có phần xử lý bằng C++, vừa có giao diện hỗ trợ người dùng kiểm tra và trình bày kết quả dễ hơn.
