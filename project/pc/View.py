from tkinter import *

class GUI:
    def __init__(self):
        self.root = Tk("Operator Dashboard")
        self.root.configure(
            height = self.root.winfo_screenheight() / 2,
            width = self.root.winfo_screenwidth() / 2
        )
        self.root.resizable = False
        self.frame = Frame(self.root)
        self.frame.grid(row = 0, column = 0)

    def tempReset(self):
        print("Temperature reset")

    def emptyContainer(self):
        print("Container emptied")

    def mainMenu(self, temp, level):
        self.tempLabel = Label(self.frame, text=temp)
        self.tempLabel.grid(row = 0, column = 0)
        self.tempResetButton = Button(self.frame, text="Reset temperature", command=self.tempReset)
        self.tempResetButton.grid(row = 1, column = 0)

        self.levelLabel = Label(self.frame, text=level)
        self.levelLabel.grid(row = 0, column = 1)
        self.emptyButton = Button(self.frame, text="Empty container", command=self.emptyContainer)
        self.emptyButton.grid(row = 1, column = 1)
        
        self.root.update()

    def update(self, temp, level):
        self.tempLabel.configure(text=temp)
        self.levelLabel.configure(text=level)
        self.root.update()