# SQL-Database-Manager
An SQL Database Manager, implemented in QT, C++ and SQLite.

I find SQL really powerful to use and so here I have created a small Database using SQLite and I'm using QT and C++ to interact and query it. For this to work the Sql module needs to be imported into QT and the QtSql Header file included. Once this is done and qmake is rerun, the project can take advantage of using the SQL Language directly.

Once the connection to the database is made, it's then just a matter of preparing and creating the SQL Statements you wish to use and executing them on the database. The typical Select, Update, Delete commands are sufficient to obtain all the functionality to manage the database. 

By Clicking on any entry, or any column of it, its details populate the edit fields so you are then free to adjust them. Otherwise you can delete entries and add new ones as you wish. The database itself is displayed through a TableView which is loaded via a Select * statement applied to the database.

I also implemented a live search feature so that you can pull up all entries which have a certain Job/Profession. As you type your search string, the database is queried for a match and shows the results.

https://user-images.githubusercontent.com/111576658/201349413-91f5a052-2ca7-4b1f-ad46-cc5d496faf09.mp4

