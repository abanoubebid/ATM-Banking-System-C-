🏦 ATM Banking System – C++ Console Application

A complete ATM simulation system built using C++, implementing real-world banking operations with file-based data persistence and clean modular design.

This project mimics how an actual ATM machine works, allowing users to securely log in and perform financial transactions such as deposits, withdrawals, and balance inquiries.

It was designed with a focus on:

Problem solving

File handling

Data structures

Clean logic design

System architecture

🚀 Features

✅ Secure login using Account Number and PIN
✅ Deposit money
✅ Quick Withdraw (predefined amounts like real ATMs)
✅ Normal Withdraw (custom amount with validation)
✅ Balance checking
✅ Persistent storage using text files
✅ Data parsing and record serialization
✅ Input validation and error handling
✅ Menu-driven interactive interface

🧠 Technical Concepts Used

Structs & Data Modeling

Vectors (Dynamic arrays)

File I/O (fstream)

String parsing

Recursion vs looping control

References & memory optimization

Modular function design

Clean separation of logic

🗂 Project Structure

The system is divided into:

Authentication (Login system)

Client Data Loader

Transaction Manager

File Manager

ATM Interface (Menus)

Balance Processing Logic

💾 Data Storage Format

Client records are stored in a text file using a custom delimiter:

AccountNumber#//#Pin#//#Name#//#Phone#//#Balance

This simulates a lightweight database.

🎯 Learning Outcomes

Through this project, I practiced:

Designing real-world systems from scratch

Writing clean and maintainable C++ code

Managing persistent data without databases

Debugging logic and memory issues

Thinking like a software engineer, not just a coder

🛠 Tech Stack

C++

STL (vector, string)

fstream

Console UI

🔮 Future Improvements

Convert to OOP architecture

Add Admin panel

Add user creation/deletion

Encryption for PINs

Database integration (SQL)

GUI version
