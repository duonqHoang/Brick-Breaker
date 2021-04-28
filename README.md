# Brick Breaker
 
	Game Phá Gạch huyền thoại

Các chức năng chính của SDL2 và hoạt động của game (renderer, các hàm load Texture, kiểm tra va chạm ...) được đưa vào 1 class RenderWindow, các vật thể có 1 class Entity riêng.

Khai báo, khởi tạo, nhập highscore, vòng lặp game, xuất highscore, xóa dữ liệu và thoát game.

Demo: https://youtu.be/pySWRKHNbTY

Cách chơi:
	
	- Sử dụng nút sang trái/phải để điều khiển thanh trượt bên dưới.
	
	- Bấm Space để bắt đầu trò chơi.
	
	- Hướng bay của bóng phụ thuộc vào vị trí va chạm với thanh trượt. 
	
	- Cố gắng ghi thật nhiều điểm bằng cách phá nhiều combo gạch nhất trước khi bóng chạm trở lại thanh.
	
	- Bóng sẽ bay nhanh hơn mỗi khi chạm vào thanh.
	
	- Phá hết gạch sẽ sang level mới (Hiện chỉ có 5 level)

Điểm tự chấm: ~8 điểm

Tham khảo:
	
	- Lazyfoo: load nhạc, kiểm tra va chạm, sử dụng SDL_ttf 
	
	- Bố cục game và 1 vài hàm cơ bản : https://www.youtube.com/watch?v=KsG6dJlLBDw&list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS
	
	- Âm thanh, hình ảnh từ https://www.kenney.nl/assets.

Phát triển ở các phiên bản sau:
	
	- Level mới
	
	- Menu điều khiển
	
	- Thêm nhạc nền, hiệu ứng và có thể điều chỉnh được
	
	- Tăng sức mạnh khi phá gạch đặc biệt (thêm bóng, giảm tốc độ bóng...)

	- Chế độ chơi mới
	

