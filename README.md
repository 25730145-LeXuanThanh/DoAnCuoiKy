# Đồ Án Cuối Kỳ: Trò Chơi Xếp Gạch (Tetris Game) - Nhóm 1

<p align="center">
  <img src="https://img.shields.io/badge/Language-C++-blue?style=for-the-badge&logo=c%2B%2B" alt="C++">
</p>

---

##  Thành Viên Tham Gia Dự Án

| Tên | Mã Số Sinh Viên | 
| :--- | :---: | 
| **Trần Hoàng Nam** | `25730126` | 
| **Lê Xuân Thạnh** | `25730145` | 
| **Võ Lê Anh Tài** | `25730143` | 
| **Trần Huỳnh Uyển Nhi** | `25730129` | 
| **Dương Ngọc Thanh Khôi** | `25730117` | 

---

## Hướng Dẫn Chạy Trò Chơi

### Cách 1: Chạy trực tiếp file thực thi (`.exe`)
1. Giải nén file `.zip` kèm theo.
2. Tìm và nhấp đúp chuột vào file `main.exe`.

---

### Cách 2: Biên dịch bằng Code::Blocks
1. Mở **Code::Blocks**, tạo một Console Project mới (`File > New > Project... > Console Application`).
2. Xóa bỏ file `main.cpp` mặc định mà template tự sinh ra.
3. Chọn thanh công cụ **Project** > **Add Files...**, sau đó bôi chọn cả 3 file: `main.cpp`, `block.cpp` và `blocks.cpp`.
4. Nhấn tổ hợp phím `F9` (hoặc chọn `Build > Build and run`) để chạy.

---

### Cách 3: Biên dịch bằng Visual Studio Code

1. Di chuyển cả 3 file nguồn (`main.cpp`, `block.cpp`, `blocks.cpp`) vào cùng **một thư mục duy nhất**.
2. Khởi động VS Code, chọn `File > Open Folder...` và trỏ tới thư mục chứa code đó.
3. Mở Terminal tích hợp bằng tổ hợp phím ``Ctrl + ` `` (hoặc vào `Terminal > New Terminal`).
4. Gõ lệnh rồi nhấn **Enter**:
   ```bash
   g++ main.cpp -o main
5. Chạy chương trình bằng lệnh:
   ```bash
   ./main.exe
