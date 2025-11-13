# ⚡ Typing Speed Test (TUI) — C Project

A **Terminal User Interface (TUI)** typing test built in **C** using the **ncurses library**.  
The app loads words from a text file, runs a **60-second typing test**, and displays **live feedback**, **countdown timer**, and **final results** such as **WPM** and **accuracy**.

---

## 🧠 Features

✅ Interactive **TUI** built with `ncurses`  
✅ **Live countdown** timer during the test  
✅ **Color feedback** — green for correct and red for incorrect words  
✅ Real-time progress (typed, correct, incorrect)  
✅ Reads words from an external file (`data/words.txt`)  
✅ Shows **accuracy**, **WPM**, and **summary results**  
✅ Cleanly exits and resets terminal on quit  

---

## ⚙️ Requirements

You need to have:
- GCC compiler  
- `make` tool  
- `ncurses` library installed  

### Install ncurses (Linux)
```bash
sudo apt update
sudo apt install libncurses5-dev libncursesw5-dev
```
### How to run this project 
```bash
git clone https://github.com/anandbhalerao18/typing_test
make clean && make
./build/typing_test
```
