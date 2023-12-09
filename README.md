# HotelSystem
A C++ GUI application in reservation for a hotel, done in qt.
To run the program, install Qt creator first and create a project with Qt widgets Application,
build system cmake, Kit Qt 6.7.0 MinGW 64-bit. The program should then properly configured.
Copy all the things besides README to this file and then Click on Run to run the project. If you
open the project directly, the build configuration may has some issues.

There are 3 types of hotels, each with 10 rooms. Customers can book anyone. Customers also need to
fill in their name, phone number, and choose an order time. If the hotel the customer
wants to book has no available rooms, it will display booking failed, try other hotels. After
booking, a receipt will be printed to the customer. The receipt contains the price, time,
which hotel and which room. The details of the customers order will be displayed on the
receipt. After ordering, all orders will be stored in the txt file. The last two options are
displayed by message box, and the first option and main window are displayed by GUI.
