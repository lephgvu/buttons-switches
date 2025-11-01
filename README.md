# 🚦 LAB 3 – BUTTONS & SWITCHES (Traffic Light System using STM32F103C6)

## 🧩 Giới thiệu

Bài Lab 3 thuộc môn **Vi điều khiển (Microcontroller Systems)**, nhằm giúp sinh viên:
- Làm quen với **xử lý nút nhấn** có chống dội (debounce).
- Sử dụng **Finite State Machine (FSM)** để quản lý chế độ hoạt động.
- Ứng dụng điều khiển **mô hình đèn giao thông** 2 chiều.
- Hiển thị **thời gian đếm và chế độ hoạt động** bằng **LED 7 đoạn (multiplexing)**.

---

## ⚙️ Mục tiêu
1. Hiểu và lập trình được **button input** với xử lý chống dội.
2. Hiển thị thông tin trên **LED giao thông và 7 đoạn**.
3. Thiết kế và mô phỏng **hệ thống đèn giao thông thông minh** với nhiều chế độ điều chỉnh.
4. Triển khai mô hình trên **STM32CubeIDE + Proteus**.

---

## 🧠 Mô hình trạng thái (FSM)

Dưới đây là sơ đồ FSM tổng thể của hệ thống đèn giao thông:

<img width="1052" height="653" alt="lab3fsm" src="https://github.com/user-attachments/assets/0de02144-540c-4054-afd9-b2d6a7c34aaf" />

### 🔹 Giải thích FSM
- **Mode 1 (Normal)**: hệ thống hoạt động tự động, luân phiên các pha:
  - `RED_GREEN → RED_AMBER → GREEN_RED → AMBER_RED`
  - Mỗi pha được điều khiển bằng timer và tự động chuyển khi hết thời gian.
- **Mode 2 (Edit Red)**: chỉnh thời gian đèn đỏ.
- **Mode 3 (Edit Amber)**: chỉnh thời gian đèn vàng.
- **Mode 4 (Edit Green)**: chỉnh thời gian đèn xanh.

Các nút điều khiển:
| Nút | Chức năng |
|------|------------|
| BTN1 | Chuyển mode |
| BTN2 | Tăng giá trị thời gian |
| BTN3 | Xác nhận và lưu giá trị |

---

## 🧩 Sơ đồ nguyên lý (Proteus)

Hệ thống được mô phỏng trên Proteus 8 với vi điều khiển **STM32F103C6**:

<img width="1259" height="886" alt="proteus" src="https://github.com/user-attachments/assets/11d0ac69-747b-42d7-8aa7-7ae7b5e24f3d" />

### 🧾 Mô tả phần cứng:
- **6 LED giao thông** (RED, YELLOW, GREEN) cho 2 hướng.
- **4 LED 7 đoạn** hiển thị `thời gian` và `mode`.
- **3 nút nhấn** điều khiển chức năng.
- **Transistor PNP** điều khiển multiplex cho LED 7 đoạn.

---

## 💡 STM32 Pin Configuration (File .ioc)

Cấu hình trong **STM32CubeIDE (.ioc):**

<img width="629" height="580" alt="lab3" src="https://github.com/user-attachments/assets/61f6b267-e683-474f-8d65-53e3b8a5b2ca" />


| Thành phần | GPIO | Chức năng |
|-------------|-------|------------|
| BTN1–BTN3 | PA1–PA3 | Input – nút nhấn |
| LED giao thông | PA4–PA9 | Output – RED/GREEN/YELLOW |
| LED 7 đoạn | PB0–PB15 | Output điều khiển các segment |
| EN0–EN3 | PA10–PA13 | Multiplex enable |

---

## 🧮 Cấu trúc phần mềm

### 🔹 Module `button.c`
- Đọc và chống dội tín hiệu nút nhấn bằng **3 buffer mẫu**.
- Sử dụng `buttonFlag[]` để phát hiện sự kiện nhấn một lần.
- Hỗ trợ **auto-release** khi nhấn giữ quá lâu.

### 🔹 Module `display.c`
- Quản lý LED giao thông và LED 7 đoạn.
- Hàm `setLEDs()` điều khiển trạng thái RED/YELLOW/GREEN.
- Hàm `blinkLEDs()` dùng trong các mode chỉnh thời gian.
- Hàm `update7SEG()` hiển thị multiplex 4 LED 7 đoạn.

### 🔹 Module `fsm.c`
- Xây dựng FSM chính của chương trình:
  - `MODE_1_NORMAL`
  - `MODE_2_EDIT_RED`
  - `MODE_3_EDIT_AMBER`
  - `MODE_4_EDIT_GREEN`
- Sử dụng nút nhấn để **chuyển mode** hoặc **tăng giá trị**.
- Gọi `setLEDs()`, `blinkLEDs()` và `update7SegBuffer()` tương ứng với mỗi trạng thái.

### 🔹 Module `software_timer.c`
- Cung cấp **timer mềm** hoạt động theo ngắt định kỳ (10ms).
- Cho phép quản lý thời gian đếm trong FSM và LED.

---

## 🧰 Cách build và chạy

### 🪜 1. Cấu hình IDE
- Mở project trong **STM32CubeIDE**.
- Chọn vi điều khiển: `STM32F103C6Tx`.
- Build project để sinh file `.hex`.

### 🪜 2. Mô phỏng trong Proteus
1. Mở file **Proteus schematic (.pdsprj)**.
2. Kết nối `MCU` với file `.hex` vừa build.
3. Chạy mô phỏng và quan sát hoạt động LED & 7 đoạn.

---

## 🎬 Kết quả mô phỏng

| Mode | LED hoạt động | Hành vi |
|------|----------------|----------|
| Mode 1 | Đèn hoạt động tự động | Chu kỳ RED–AMBER–GREEN luân phiên |
| Mode 2–4 | LED cùng màu nhấp nháy | Thay đổi thời gian tương ứng |
| 7-seg | Hiển thị thời gian và mode | Cập nhật liên tục |

---

## 📚 Kết luận
Qua bài Lab 3, hệ thống đã:
- Ứng dụng **FSM** và **button debounce** hiệu quả.
- Hiển thị đồng bộ giữa **LED giao thông** và **7 đoạn**.
- Tách biệt rõ **phần mềm – phần cứng – hiển thị**, dễ mở rộng.
- Làm nền tảng cho các bài lab tiếp theo (VD: UART, LCD, Timer nâng cao).

## 🖼️ Phụ lục hình ảnh
- FSM Diagram  
- STM32 Pin Mapping (.ioc)  
- Proteus Schematic  

