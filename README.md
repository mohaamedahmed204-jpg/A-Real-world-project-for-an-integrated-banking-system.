# A-real-world-project-for-an-integrated-banking-system.

# 🚀 Integrated Banking System (C++).        

## 📌 Table of Contents.   

    📖 About The Project

    🏛️ System Architecture & Structure

    ✨ Core Features & Modules

    📂 Project Directory & Files Breakdown

    🛠️ Technical Stack & Libraries

    🚀 Getting Started & Execution
    
    👤 Author

    🙏 Acknowledgments

 # 📖 About The Project

 The Integrated Banking System is a comprehensive console-based enterprise-grade application designed to simulate real-world core banking operations. Built with strict adherence to Object-Oriented Programming (OOP) principles, design patterns, and modular separation of concerns, the system handles client accounts, transaction processing, multi-currency exchange rates, user permission management, and secure system logging.

 # 🏛️ System Architecture & Structure

 The project follows a clean, scalable architectural pattern, decoupling core business logic entities from user interface screens and system utility libraries:

    CoreObjects: Houses the core foundational business entities (clsBankClient, clsUser, clsCurrency, clsPerson).

    Lib: Contains utility and helper classes handling validations, string manipulation, date calculations, and general operations.

    Screens: Organizes the presentation layer into distinct functional modules (Clients, Currency, Transactions, Users, and Login/Main dashboards).

# ✨ Core Features & Modules

👥 Client Management Module: Add, update, delete, search, and list bank clients with persistent file storage.

💳 Transactions & Operations Module:

    Deposit and Withdraw funds securely.

    Real-time Total Balances monitoring.

    Internal Transfer system with dedicated transaction logging (TransferLog.txt).

💱 Currency Exchange Module: Currency calculator, exchange rate tracking, currency listing, and rate updates (Currencies.txt).

🔐 User & Permissions Management: Multi-tier administrative controls, user registration tracking, and secure login screens (RegisterLogins.txt, Users.txt).

🔒 Security & Encryption: Integrated key encryption and strict input validation layers.

# 📂 Project Directory & Files Breakdown
```text
📦 real-world-project-for-an-integrated-banking-system
 ┣ 📂 CoreObjects/
 ┃  ┣ 📜 clsBankClient.h
 ┃  ┣ 📜 clsCurrency.h
 ┃  ┣ 📜 clsLoginScreen.h
 ┃  ┣ 📜 clsMainScreen.h
 ┃  ┣ 📜 clsPerson.h
 ┃  ┣ 📜 clsScreen.h
 ┃  ┣ 📜 clsUser.h
 ┃  ┣ 📜 Global.h
 ┃  ┗ 📜 InterfaceCommunication.h
 ┣ 📂 Lib/
 ┃  ┣ 📜 clsDate.h
 ┃  ┣ 📜 clsInputValidate.h
 ┃  ┣ 📜 clsString.h
 ┃  ┗ 📜 clsUtil.h
 ┣ 📂 Screens/
 ┃  ┣ 📂 Clients/ (Add, Delete, Find, List, Update Screens)
 ┃  ┣ 📂 Currency/ (Calculators, Exchange Main, Lists, Rates)
 ┃  ┣ 📂 Transactions/ (Deposit, Withdraw, Total Balances, Transfers)
 ┃  ┗ 📂 Users/ (User Management, Add, Delete, Find, List, Login Register)
 ┣ 📄 Clients.txt
 ┣ 📄 Currencies.txt
 ┣ 📄 RegisterLogins.txt
 ┣ 📄 TransferLog.txt
 ┣ 📄 Users.txt
 ┗ 📜 test.cpp
```

# 🛠️ Technical Stack & Libraries

Language: C++

Paradigm: Object-Oriented Programming (OOP), Inheritance, Polymorphism, Encapsulation.

Data Storage: Flat-file database architecture (.txt structured storage).

Development Environment: Visual Studio / VS Code.

# 🚀 Getting Started & Execution
```text
g++ test.cpp -ICoreObjects -ILib -IScreens -IScreens/Clients -IScreens/Currency -IScreens/Transactions -IScreens/Users -o test
.\test.exe
```

# 👤 Author

* Mohamed Ahmed Gwiada 

# 🙏 Acknowledgments

This project is part of the Programming Advices Training Track led by:

* 👨‍🏫 Dr. Mohamed Abouhadhood
* 💻 Platform: Programming Advices
