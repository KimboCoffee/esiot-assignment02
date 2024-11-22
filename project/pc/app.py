import MessageHandler
import View
import time

gui = View.GUI()
i = 0
gui.mainMenu(i, i+1)

while True:
    gui.update(i, i+1)
    i = i+1
    time.sleep(0.200)