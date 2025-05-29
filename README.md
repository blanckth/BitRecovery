Certainly! Below is a structured and bilingual (English-Persian) README.md for the BitRecovery project. The Persian sections are formatted using HTML with right-to-left (RTL) direction for proper display on GitHub.
BitRecovery
🔍 Overview

BitRecovery is an advanced forensic tool designed for low-level disk analysis and recovery. It enables investigators and data recovery professionals to examine disk images at the sector level, identify partitioning schemes (MBR/GPT), detect encryption signatures (e.g., BitLocker), and extract critical metadata.
📁 Project Structure
`
BitRecovery/
├── src/
│   ├── main.c
│   ├── modules/
│   │   ├── image/
│   │   │   ├── image.h
│   │   │   └── image.c
│   │   ├── disk/
│   │   │   ├── disk.h
│   │   │   └── disk.c
│   │   └── disk/sector/
│   │       ├── sector.h
│   │       └── sector.c
│   └── utils/
│       └── times/
│           ├── times.h
│           └── times.c
└── README.md
`
⚙️ Build Instructions

To compile the project:

git clone https://github.com/blanckth/BitRecovery.git
cd BitRecovery/src
make

Ensure that you have the necessary build tools installed (e.g., gcc, make).
🚀 Usage

./bitrecovery [ImagePath/DiskPath] [Sector Number] [Sector Size] [Sector Count]

    ImagePath/DiskPath: Path to the disk image or device.

    Sector Number: (Optional) Starting sector number (default: 0).

    Sector Size: (Optional) Size of each sector in bytes (default: 512).

    Sector Count: (Optional) Number of sectors to read (default: 1).

Example:
`
./bitrecovery /dev/sda 0 512 1
`
🧩 Module Descriptions
main.c

    Entry point of the application.

    Parses command-line arguments.

    Initializes modules for image and disk handling.

    Reads and displays sector data.

modules/image/image.c & image.h

    Handles opening and closing of disk image files.

    Extracts metadata such as file size, timestamps, and partitioning scheme.

    Detects presence of MBR, GPT, and BitLocker signatures.

modules/disk/disk.c & disk.h

    Interfaces with disk devices or image files.

    Retrieves disk-specific information like block size.

    Provides functions to open and close disk handles.

modules/disk/sector/sector.c & sector.h

    Reads raw sector data from the disk.

    Provides functions to read single or multiple sectors.

    Formats and displays sector data in hexadecimal and ASCII.

utils/times/times.c & times.h

    Utility functions for formatting and displaying timestamps.

🛠️ Features

    Low-Level Disk Access: Read raw sectors directly from disk or image files.

    Partition Detection: Identify MBR and GPT partitioning schemes.

    Encryption Detection: Detect presence of BitLocker encryption.

    Metadata Extraction: Retrieve detailed file and disk metadata.

    Formatted Output: Display sector data in a readable hex and ASCII format.

🧪 Sample Output

`
'''
#. Application Start Running :  ./bitrecovery  /dev/sda
#. 
#.     Loading Image File :        /dev/sda
#.         File Open Timestamp: 2025-05-29 23:57:16
#.         Filename: sda
#.         Resume Sector: 0
#.         Sector Block Size: 512
#.         Partitioning scheme: MBR (Master Boot Record)
#.         BitLocker presence: Not found
#. 
#.         File Metadata:
#.             Inode: 12345678
#.             Device ID: 2049
#.             UID (Owner): 0
#.             GID (Group): 0
#.             File Size: 500107862016 bytes
#.             Permissions: 644 (octal)
#.             Last Access Time: 2025-05-29 22:00:00
#.             Last Modification Time: 2025-05-29 21:00:00
#.             Last Status Change Time: 2025-05-29 20:00:00
#.             I/O Block Size: 4096 bytes
#.             Block Count: 976773168 Blocks
#. 
#.     Loading Disk:
#.         Disk Metadata:
#.             Disk Path: /dev/sda
#.             Disk Name: sda
#.             Disk File Descriptor: 3
#.             Soft block size: 512
#.             Logical block size: 512
#.             Physical block size: 4096
#.             Disk Block Size: 512
#. 
#.         Loading Sectors:
#.             Read sector 0 successfully.
#.             Dumping 1 Sector(s) (512 bytes):
#.             ============================ Sector 0 ============================
#.             00000000  eb 3c 90 4d 53 44 4f 53 35 2e 30 00 02 08 00 00   .<.MSDOS5.0.....
#.             00000010  02 00 00 00 00 f8 00 00 3f 00 ff 00 3f 00 00 00   ......?..?.?...
#.             ...
'''
`

🧠 Notes

    Ensure you have the necessary permissions to access raw disk devices.

    Use caution when working with disk devices to prevent data loss.

    The tool is intended for forensic and data recovery purposes.

📜 License

This project is licensed under the MIT License.
🧑‍💻 Author

    blanckth - GitHub Profile

<div dir="rtl" align="right">
بیت‌ریکاوری (BitRecovery)
🔍 معرفی

بیت‌ریکاوری یک ابزار پیشرفته برای تحلیل و بازیابی داده‌ها در سطح پایین دیسک است. این ابزار به متخصصان بازیابی داده و کارشناسان جرم‌شناسی دیجیتال امکان می‌دهد تا تصاویر دیسک را در سطح سکتور بررسی کرده، ساختارهای پارتیشن‌بندی (MBR/GPT) را شناسایی کرده، امضاهای رمزنگاری (مانند BitLocker) را تشخیص داده و متادیتای حیاتی را استخراج کنند.
📁 ساختار پروژه
`
BitRecovery/
├── src/
│   ├── main.c
│   ├── modules/
│   │   ├── image/
│   │   │   ├── image.h
│   │   │   └── image.c
│   │   ├── disk/
│   │   │   ├── disk.h
│   │   │   └── disk.c
│   │   └── disk/sector/
│   │       ├── sector.h
│   │       └── sector.c
│   └── utils/
│       └── times/
│           ├── times.h
│           └── times.c
└── README.md
`
⚙️ دستورالعمل ساخت

برای کامپایل پروژه:

git clone https://github.com/blanckth/BitRecovery.git
cd BitRecovery/src
make

اطمینان حاصل کنید که ابزارهای لازم برای ساخت (مانند gcc و make) نصب شده‌اند.
🚀 نحوه استفاده

./bitrecovery [مسیر تصویر/دیسک] [شماره سکتور] [اندازه سکتور] [تعداد سکتورها]

    مسیر تصویر/دیسک: مسیر به فایل تصویر دیسک یا دستگاه.

    شماره سکتور: (اختیاری) شماره سکتور شروع (پیش‌فرض: 0).

    اندازه سکتور: (اختیاری) اندازه هر سکتور به بایت (پیش‌فرض: 512).

    تعداد سکتورها: (اختیاری) تعداد سکتورهایی که باید خوانده شوند (پیش‌فرض: 1).

مثال:

./bitrecovery /dev/sda 0 512 1

🧩 توضیحات ماژول‌ها
main.c

    نقطه ورود برنامه.

    تجزیه آرگومان‌های خط فرمان.

    مقداردهی اولیه ماژول‌های مربوط به تصویر و دیسک.

    خواندن و نمایش داده‌های سکتور.

modules/image/image.c و image.h

    مدیریت باز و بسته کردن فایل‌های تصویر دیسک.

    استخراج متادیتا مانند اندازه فایل، زمان‌های دسترسی و ساختار پارتیشن‌بندی.

    تشخیص وجود MBR، GPT و امضاهای BitLocker.

modules/disk/disk.c و disk.h

    ارتباط با دستگاه‌های دیسک یا فایل‌های تصویر.

    بازیابی اطلاعات خاص دیسک مانند اندازه بلوک.

    ارائه توابع برای باز و بسته کردن دسته‌های دیسک.

modules/disk/sector/sector.c و sector.h

    خواندن داده‌های خام سکتور از دیسک.

    ارائه توابع برای خواندن یک یا چند سکتور.

    فرمت‌بندی و نمایش داده‌های سکتور به صورت هگزادسیمال و ASCII.

utils/times/times.c و times.h

    توابع کمکی برای فرمت‌بندی و نمایش زمان‌ها.

🛠️ ویژگی‌ها

    دسترسی سطح پایین به دیسک: خواندن سکتورهای خام مستقیماً از دیسک یا فایل‌های تصویر.

    تشخیص پارتیشن: شناسایی ساختارهای پارتیشن‌بندی MBR و GPT.

    تشخیص رمزنگاری: تشخیص وجود رمزنگاری BitLocker.

    استخراج متادیتا: بازیابی متادیتای دقیق فایل و دیسک.

    خروجی فرمت‌شده: نمایش داده‌های سکتور به صورت قابل خواندن در فرمت هگزادسیمال و ASCII.

</dev>