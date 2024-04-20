# FrogGun
SDL2_Game_Project
Đây là bài tập lớn về làm game trên sdl2 trong học phần Lập trìng nâng cao
Sinh viên: Dương Đình Minh
MSV: 23020110
## Giới thiệu về game
FrogGun là một trò chơi phiêu lưu hành động nơi người chơi điều khiển một chú ếch có khả năng bắn đạn để chiến đấu với các con quái vật. Trò chơi có nhiều tổng cộng 4 màn chơi và 1 boss cuối. Hãy đánh bại kẻ địch và đạt điểm số cao nhất.   
## Hướng dẫn cài đặt
- Tải xuống hoặc clone repo này về máy
- mở terminal lên và chạy lệnh
``` shell
mingw32-make
```
- hoặc
``` shell
g++ -I base -I src/include -L src/lib -o main main.cpp base/enemy/*.cpp base/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
./main
```
- hoặc có thể tạo fie task.json trong vscode và thêm phần này vào để có thể run code trong vscode
``` json
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${fileDirname}\\main.cpp",
                "${fileDirname}\\base\\**.cpp",
                "${fileDirname}\\base\\enemy\\**.cpp",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe",
                "-Isrc/include",
                "-Lsrc/lib",
                "-lmingw32",
                "-lSDL2main",
                "-lSDL2",
                "-lSDL2_image",
                "-lSDL2_mixer",
                "-lSDL2_ttf"
            ],
```
## Hướng dẫn chơi:
- Người chơi bắt đầu với 10 máu và 6 viên đạn
- có 4 chế độ `easy`, `medium`, `hard`, `very hard`
- các chế độ trên `easy` sẽ khó hơn khăn, nhiều kẻ thù hơn, nhiều bẫy hơn, nhiều quái ngẫu nhiên hơn
- Nhấn `a`, `d`, `w` để di chuyển trái/phải/lên
- Nhấn `w` lần thứ 2 để double jump
- Nhấn `1`, `2`, `4` để chuyển trạng thái bình thường/tăng tốc/bắn nhiều đạn
- Nhấn `q`, `e` để đổi loại đạn
- Nhấn `SHIFT` để dash
- Nhấn `ESC` để pause game
## Tài liệu tham khảo
- Tham khảo và học hỏi về hướng đối tượng và thư viện SDL2 từ [PhatTrienPhanMem123AZ](https://www.youtube.com/@PhatTrienPhanMem123AZ) và [lazyfoo](https://lazyfoo.net/tutorials/SDL/index.php)
- Các file game asset được lấy từ [itch.io](https://itch.io/game-assets/free)
## Kiến thức sử dụng
- OOP (Lớp, đối tượng, tính đa hình, tính kế thừa, virtual fuction và override)
- Một số kiến thức toán học, hình học
- Kiến thức đã học trong học phần Lập trình nâng cao (INT2215)
- Thư viện SDL2
- Các dùng git và github cơ bản
## Ngưỡng điểm mong muốn
- Điểm số em mong muốn là khoảng ngưỡng 8.5.
- Lí do em mong muốn được ngưỡng điểm trên là đồ họa tương đối đẹp, âm thanh sinh động và nhân vật di chuyển mượt mà. Đã thiết kế được đầy đủ  giao diện cơ bản cho game. Sử dụng OOP một cách tương đối hợp lí.
