# 🎵 MP3 Tag Editor CLI (C Project)

A **command-line based MP3 Tag Viewer & Editor** written in **C**, with **color-coded and emoji-enhanced outputs** for a more user-friendly experience.
This project allows you to **view** and **edit ID3 tags** (Title, Artist, Album, Year, Composer, Genre) of MP3 files directly from the terminal.

---

## 🚀 Features

* ✅ View MP3 tag information in a clean, colorful format.
* ✅ Edit specific tags (Title, Artist, Album, etc.) in an MP3 file.
* ✅ Filename validation with friendly error messages.
* ✅ Loading animations for a smoother CLI experience.
---

## 📂 Project Structure

```
├── main.c         # Entry point, handles CLI arguments
├── mp3.c          # Core logic for viewing & editing MP3 tags
├── header.h       # Function prototypes + centralized color codes
├── validation.h   # MP3 filename validation with friendly messages
```

---

## ⚙️ Compilation

Use `gcc` to compile the project:

```bash
gcc main.c mp3.c -o mp3editor
```

---

## 🎮 Usage

### 📖 View Tags

```bash
./mp3editor -v song.mp3
```

👉 Displays all available ID3 tags with emojis (🎵 Title, 👤 Artist, 💿 Album, etc.)

### ✍️ Edit Tags

```bash
./mp3editor -e song.mp3 -t "New Title"
./mp3editor -e song.mp3 -A "New Artist"
./mp3editor -e song.mp3 -y "2025"
```

👉 Updates the selected tag in the MP3 file.

### 🆖 Help Menu

```bash
./mp3editor -h
```

👉 Displays usage instructions and available options.

---

## 🌈 Example Output

```
⏳ Fetching MP3 tag information...
================ MP3 TAG INFORMATION ================
🎵 Title     : Shape of You
👤 Artist    : Ed Sheeran
💿 Album     : Divide
📅 Year      : 2017
✍️  Composer  : Ed Sheeran
🎶 Genre     : Pop
=====================================================
```

---

## 🔧 Dependencies

* Standard C libraries (`stdio.h`, `stdlib.h`, `string.h`, `unistd.h`, `ctype.h`)
* ANSI color-supporting terminal (Linux, macOS, WSL, Git Bash on Windows)

---

## 🌟 Future Enhancements

* Add support for more ID3 frames (e.g., Lyrics, Track Number).
* Export tag information to JSON or TXT.
* Batch editing of multiple MP3 files.
* Cross-platform GUI version.

---

## 👨‍💻 Author

Developed by **Krishnaiah Mandala**
📌 Project created as part of practice in **C programming (Modular Design & File Handling)**

---

## 📜 License

This project is open-source and available under the **MIT License**.
