# BitRecovery
Read https://github.com/blanckth/BitRecovery.git and all the project files and class 
Review and Optimized Ai Perfection by Smart Intel
make a preview Presentation for the "Advanced Forensic Bit Level Recovery Tool" Report for my Clients.
twe Lang Comments and Explanation English And Persian

## https://github.com/blanckth/BitRecovery.git

### blanckth/BitRecovery/src
### blanckth/BitRecovery/src/main.c
### src/modules
### src/modules/image
### src/modules/image/image.h
### src/modules/image/image.c
### src/modules/disk
### src/modules/disk/disk.h
### src/modules/disk/disk.c
### src/modules/disk/sector
### src/modules/disk/sector/sector.h
### src/modules/disk/sector/sector.c

Certainly! Here's a comprehensive overview of the BitRecovery project, an advanced forensic bit-level recovery tool, along with a bilingual (English and Persian) presentation outline tailored for your clients.
🔍 BitRecovery: Advanced Forensic Bit-Level Recovery Tool

Overview:
BitRecovery is an open-source forensic tool designed for low-level disk analysis and recovery. It enables investigators to read, interpret, and extract data directly from disk sectors, making it invaluable for scenarios involving damaged, encrypted, or partially overwritten partitions.

Key Features:

    Sector-Level Analysis: Direct reading and interpretation of disk sectors.

    Partition Table Parsing: Supports both MBR and GPT partition schemes.

    BitLocker Detection: Identifies BitLocker-encrypted volumes.

    Modular Architecture: Organized into distinct modules for image handling, disk operations, and sector analysis.
    Wikipedia

📁 Project Structure

The project is organized into the following directories:

    src/main.c: Entry point of the application; handles argument parsing and orchestrates module interactions.

    src/modules/image/: Manages image file operations, including opening, reading metadata, and closing.

    src/modules/disk/: Handles disk-level operations, such as opening disk handles and retrieving disk metadata.

    src/modules/disk/sector/: Provides functionalities for reading and printing disk sectors.
    MDPI+1Magnet Forensics+1

🧠 Technical Highlights
1. Image Handling (image.c)

    File Metadata Extraction: Retrieves information like inode, device ID, owner UID/GID, file size, permissions, and timestamps.

    Partition Scheme Detection: Analyzes the first bytes of the image to determine if it's MBR or GPT.

    BitLocker Detection: Checks for BitLocker signatures to identify encrypted volumes.

2. Disk Operations (disk.c)

    Disk Metadata Retrieval: Uses ioctl calls to get block sizes (soft, logical, physical).

    Disk Handle Management: Opens and closes disk handles safely.

3. Sector Analysis (sector.c)

    Sector Reading: Reads specified sectors from the disk using lseek and read.

    Hex Dump Printing: Displays sector data in a formatted hex dump for analysis.

🛠️ Practical Applications

    Data Recovery: Retrieve data from corrupted or damaged partitions.

    Digital Forensics: Analyze disk structures for investigative purposes.

    Educational Tool: Understand low-level disk operations and structures.
    Digital Detective+4LinkedIn+4DiskInternals+4
    DiskInternals+1Digital Detective+1

🌐 Bilingual Presentation Outline
Slide 1: Introduction

    English: Welcome to the BitRecovery Tool Overview.

    Persian: به معرفی ابزار BitRecovery خوش آمدید.
    GetData Forensics

Slide 2: Project Overview

    English: BitRecovery is an open-source tool for low-level disk analysis and recovery.

    Persian: BitRecovery یک ابزار متن‌باز برای تحلیل و بازیابی سطح پایین دیسک است.

Slide 3: Features

    English: Supports MBR/GPT, detects BitLocker, modular design.

    Persian: پشتیبانی از MBR/GPT، شناسایی BitLocker، طراحی ماژولار.

Slide 4: Technical Architecture

    English: Modular structure with separate components for image, disk, and sector operations.

    Persian: ساختار ماژولار با اجزای جداگانه برای عملیات تصویر، دیسک و سکتور.

Slide 5: Use Cases

    English: Ideal for data recovery, digital forensics, and educational purposes.

    Persian: مناسب برای بازیابی داده، جرم‌شناسی دیجیتال و اهداف آموزشی.
    www.slideshare.net+2ResearchGate+2LinkedIn+2

Slide 6: Conclusion

    English: BitRecovery empowers users with low-level disk analysis capabilities.

    Persian: BitRecovery به کاربران امکان تحلیل سطح پایین دیسک را می‌دهد.
    GetData Forensics

For more detailed information and to access the source code, please visit the BitRecovery GitHub Repository.



# 🧠 BitRecovery: Advanced Forensic Bit-Level Recovery Tool  
🔍 ابزار پیشرفته بازیابی سطح-بیتی دیجیتال (تحلیلی و جرم‌شناسی)

---

## 📌 Overview | نمای کلی

**BitRecovery** is a modular, low-level forensic disk recovery and analysis tool designed to extract and interpret raw disk data at the bit and sector level.  
This tool is ideal for forensic investigators, data recovery professionals, and researchers interested in low-level disk structures such as MBR, GPT, and BitLocker artifacts.

**BitRecovery** <div dir="rtl">

>یک ابزار متن‌باز و ماژولار برای تحلیل و بازیابی اطلاعات از سطح پایین‌ترین بخش‌های دیسک (سکتورها و بیت‌ها) است.  
این ابزار برای متخصصان جرم‌شناسی دیجیتال، بازیابی اطلاعات و پژوهشگران ساختارهای سطح پایین دیسک مثل MBR، GPT و آرتیفکت‌های BitLocker بسیار کاربردی است.
</div
---

## 📂 Project Structure | ساختار پروژه

BitRecovery/
├── src/
│ ├── main.c # Entry point of the application | نقطه شروع برنامه
│ └── modules/
│ ├── image/ # Image file handlers | مدیریت فایل‌های ایمیج
│ ├── disk/ # Disk access and metadata | اطلاعات و دسترسی دیسک
│ │ └── sector/ # Sector reading/printing | خواندن و چاپ سکتورها
│
├── README.md # This file | این فایل
├── LICENSE
└── ...


---

## 🔧 Features | ویژگی‌ها

### ✅ Sector-Level Analysis | تحلیل در سطح سکتور
- Reads raw sectors directly from disk or image files.
- نمایش سکتورها به صورت hex/ascii با فرمت تحلیل‌پذیر.

### ✅ Partition Scheme Detection | تشخیص نوع پارتیشن
- Detects both **MBR** and **GPT**.
- پشتیبانی از شناسایی و پارس ساختارهای MBR و GPT.

### ✅ BitLocker Detection | شناسایی BitLocker
- Locates BitLocker-encrypted volumes by analyzing known signatures.
- بررسی و کشف رمزنگاری BitLocker با تحلیل سیگنچرهای شناخته‌شده.

### ✅ Disk Metadata Analysis | تحلیل متادیتای دیسک
- Retrieves metadata like logical/physical sector sizes, file size, inode, and more.
- استخراج اطلاعات سیستمی فایل ایمیج، سایز سکتورها، inode و ...

### ✅ Modular Design | طراحی ماژولار
- Each function is separated by concern (image, disk, sector).
- طراحی ساختارمند برای توسعه‌پذیری و دیباگ آسان.

---

## 📘 Modules Overview | مروری بر ماژول‌ها

### 🔹 `main.c`
- Argument parser and orchestrator for calling the image and disk modules.
- پارسر آرگومان‌ها و کنترل اصلی اجرای برنامه.

---

### 🔹 `modules/image/image.c`  
**Image Module | ماژول تصویر**
- Opens disk image (`/dev/sdX` or `.img` file).
- Retrieves file-level metadata (permissions, timestamps, owner info, etc).
- Detects partition style (MBR/GPT) by inspecting sector 0.
- Detects BitLocker headers (FVE metadata signatures).

> تحلیل سطح فایل ایمیج، تشخیص نوع پارتیشن، بررسی سیگنچرهای BitLocker

---

### 🔹 `modules/disk/disk.c`  
**Disk Module | ماژول دیسک**
- Opens a low-level handle to the disk or image.
- Gets sector size info via `ioctl()`.
- Handles clean disk closing and error logging.

> بازکردن هندل سطح پایین دیسک، دریافت سایز فیزیکی/منطقی سکتور و مدیریت خطا

---

### 🔹 `modules/disk/sector/sector.c`  
**Sector Module | ماژول سکتورها**
- Reads a sector (default: 512 bytes) from any offset.
- Prints formatted hex/ascii dumps for forensic viewing.
- Modular output support for later log integration.

> خواندن سکتورهای خام و نمایش تحلیلی با فرمت قابل‌خواندن برای تحلیلگرها

---

## 🧪 Sample Output | نمونه خروجی

Sector 0:
00000000 EB 52 90 4D 53 44 4F 53 35 2E 30 00 02 01 01 00 |.R.MSDOS5.0.....|
00000010 02 E0 00 40 0B F0 09 00 ...


---

## 🎯 Use Cases | کاربردها

| Use Case         | Description (English)                             | توضیح فارسی                            |
|------------------|----------------------------------------------------|----------------------------------------|
| 🔍 Forensics      | Analyze low-level disk data for hidden evidence    | بررسی داده‌های سطح پایین دیسک برای شواهد |
| 💾 Data Recovery  | Extract data from corrupted MBR/GPT/BitLocker     | بازیابی داده از ساختارهای آسیب‌دیده     |
| 🧑‍🏫 Education      | Learn disk internals with real-world examples     | آموزش ساختارهای واقعی دیسک              |

---

## 🔐 BitLocker Signature Detection

BitRecovery detects the presence of BitLocker-encrypted volumes by inspecting early sectors (FVE metadata) for known GUIDs and magic constants.  

BitLocker volumes typically contain structures like:

0xFVE Metadata Header
Volume Master Key (VMK)
Encrypted Sector Key (ESK)


> ابزار با بررسی GUIDها و سیگنچرهای مشخص در سکتورهای ابتدایی، رمزنگاری BitLocker را تشخیص می‌دهد.

---

## 🏁 How to Build | نحوه کامپایل

```bash
git clone https://github.com/blanckth/BitRecovery.git
cd BitRecovery
make

مطمئن شوید GCC و ابزارهای بیسیک build روی سیستم لینوکس نصب هستند.

🚀 How to Use | نحوه استفاده
Read Image and Analyze:

🚀 How to Use | نحوه استفاده
Read Image and Analyze:

./bitrecovery /path/to/disk.img

Print Sector 0:

./bitrecovery -s 0 /path/to/disk.img

👨‍💻 Author | نویسنده

Salar Muhammadi
GitHub: @blanckth
Email: mhmdi.salar@gmail.com

📜 License

This project is licensed under the MIT License.
🤝 Contributions

We welcome PRs, issues, and forensic research ideas.

پیشنهادات، باگ ریپورت‌ها و ایده‌های شما برای توسعه ابزار جرم‌شناسی دیجیتال BitRecovery با آغوش باز پذیرفته می‌شود.


---
