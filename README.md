# FrogGun

SDL2_Game_Project

Sinh viên: Dương Đình Minh

MSV: 23020110

FrogGun là một trò chơi phiêu lưu hành động nơi người chơi điều khiển một chú ếch có khả năng bắn đạn để chiến đấu với các con quái vật. Trò chơi có nhiều tổng cộng 5 màn chơi và 1 boss cuối  
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
## Hướng dẫn chơi:
- Người chơi bắt đầu với 10 máu và 6 viên đạn
- có 4 chế độ `easy`, `medium`, `hard`, `very hard`
- các chế độ trên `easy` sẽ khó hơn khăn, nhiều kẻ thù hơn, nhiều bẫy hơn
- Nhấn `a`, `d`, `w` để di chuyển trái/phải/lên
- Nhấn `w` lần thứ 2 để double jump
- Nhấn `1`, `2`, `4` để chuyển trạng thái bình thường/chạy nhanh/bắn nhiều đạn
- Nhấn `q`, `e` để đổi loại đạn
- Nhấn `SHIFT` để dash
- Nhấn `ESC` để pause game
## Tài liệu tham khảo
- Tham khảo và học hỏi về hướng đối tượng và SDL2 từ [PhatTrienPhanMem123AZ](https://www.youtube.com/@PhatTrienPhanMem123AZ) và [lazyfoo](https://lazyfoo.net/tutorials/SDL/index.php)
## Kiến thức sử dụng
- Lớp, đối tượng, đa hình, kế thừa
- Toán học
- SDL2
## Ngưỡng điểm mong muốn
- Điểm số mong muốn là khoảng ngưỡng 8 - 8.5.
- Lí do mong muốn được ngưỡng điểm trên là đồ họa tương đối đẹp, âm thanh sinh động và nhân vật di chuyển mượt mà.
