import time
import os
import subprocess

def open_image_repeatedly():
    image_path = "img.png"  # Путь к изображению
    if not os.path.exists(image_path):
        print(f"Ошибка: файл {image_path} не найден!")
        return

    print("Начинаю спамить окнами через 20 минут...")
    time.sleep(20 * 60)  # Ждём 20 минут (1200 секунд)

    while True:  # Бесконечный цикл
        try:
            # Открываем изображение стандартным способом для ОС
            if os.name == 'nt':  # Windows
                os.startfile(image_path)
            elif os.name == 'posix':  # Linux/macOS
                subprocess.run(["xdg-open", image_path])  # Linux
                # subprocess.run(["open", image_path])  # macOS (раскомментировать если нужно)
            time.sleep(0.5)  # Небольшая задержка между открытиями
        except Exception as e:
            print(f"Ошибка: {e}")
            break

open_image_repeatedly()