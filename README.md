# Jhelum

## Project Structure

```bash
.
├── README.md
└── esb_endpoint
    ├── Payload.json
    ├── bmd_files  --> Uploaded BMD files get stored here in a unique directory
    │   └── 1599150636_1166897047
    │       └── HelloABC.xml
    ├── cert
    │   ├── key.pem
    │   └── server.pem
    ├── conf
    │   ├── build.conf
    │   └── esb_endpoint.conf
    ├── dh2048.pem
    ├── scripts
    │   └── SQLscript.sql ----> The script to set up the database
    └── src
        ├── adapter
        │   ├── email.c
        │   ├── email.h
        │   └── http.c
        ├── esb
        │   ├── Payload.json
        │   ├── Test_files ---> Files to be used for Unit Testing
        │   │   ├── HelloABC.xml
        │   │   ├── bmd.xml
        │   │   ├── bmdT1.xml
        │   │   ├── bmdT2.xml
        │   │   ├── bmdT3.xml
        │   │   ├── bmdT4.xml
        │   │   └── bmdT5.xml
        │   ├── bmd_parser.c
        │   ├── bmd_parser.h
        │   ├── database.c
        │   ├── database.h
        │   ├── dynamic_lookup.c
        │   ├── esb.c
        │   ├── esb.h
        │   ├── munit.c
        │   ├── munit.h
        │   ├── test_bmd_parser.c
        │   ├── test_esb
        │   ├── test_esb.c
        │   ├── transform.c
        │   ├── transport.c
        │   ├── worker.c
        │   └── xmljson.c
        └── esb_endpoint.c
```

## Essential Libraries to Install before using this Project
 Ensure that you have the essential libraries and headers , Run the following steps on the terminal
 ```bash
 Install required Libraries
 sudo apt update
 sudo apt install build-essential
 sudo apt install libssl-dev
 sudo apt install wget
 sudo apt install curl
 ```
1. Libxml2
    ```bash
    sudo apt-get install libxml2
    sudo apt-get install libxml2-dev
    ```

2. [MySql](https://dev.mysql.com/doc/mysql-apt-repo-quick-guide/en/).
3. Pthreads
4. Libcurl
5. [Kore Web Framework](https://docs.kore.io/4.0.0/install.html)


## Setting Up the MySQL Database For the Project

1. After installing MySQL get to the MySQL command line on the terminal.
```bash
Akshays-MacBook-Air:~ akshay$ mysql -u root -p
Enter password: 
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 8
Server version: 8.0.21 Homebrew

Copyright (c) 2000, 2020, Oracle and/or its affiliates. All rights reserved.

Oracle is a registered trademark of Oracle Corporation and/or its
affiliates. Other names may be trademarks of their respective
owners.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql> 
```
You should see a similar screen as above. You can replace root with your desired username.
The next step would be to run the SQL script to set up the database. The script can be found in the scripts directory inside esb_endpoint directory.
Run the following command to execute the script.
```bash
source Path/to/project/directory/esb_endpoint/scripts/SQLscript.sql;
```
This should create a database named esb_db with 4 tables.

2. Set up your Username and Password by changing corresponding fields in database.h file in src directory.

3. The tables in esb_db are as follows: 
    i. esb_request table: (These are only some rows; The rows are added as you curl the bmd.xml)
    ```bash
    mysql> select * from esb_request;
+------+--------------------------------------+--------------------------------------+--------------+--------------------+--------------------------------------+---------------------+---------------+-----------+----------------+
| id   | sender_id                            | dest_id                              | message_type | reference_id       | message_id                           | received_on         | data_location | status    | status_details |
+------+--------------------------------------+--------------------------------------+--------------+--------------------+--------------------------------------+---------------------+---------------+-----------+----------------+
| 1045 | 556E2EAA-1D5B-5BC0-BCC4-4CEB669408DA | 6323D82F-4687-433D-AA23-1966330381FE | DebitReport  | INV-PROFILE-889712 | A3ECAEF2-104A-3452-9553-043B6D25386E | 2020-08-12 10:48:00 | NULL          | available | NULL           |
| 1179 | 522E2EAA-2D5B-8BC0-FCC4-5CEB669408DA | 5223D82F-4657-333D-BA23-2966330381FE | CreditReport | INV-PROFILE-889712 | D3ECAEF2-204A-3452-9553-043B6D25386E | 2020-08-12 10:48:00 | NULL          | available | NULL           |
| 1180 | 222E2EAA-1D5B-5BC0-BCC4-4CEB669408DA | 2223D82F-4687-433D-AA23-1966330381FE | CreditReport | INV-PROFILE-889712 | F3ECAEF2-204A-3452-9553-043B6D25386E | 2020-08-12 10:48:00 | NULL          | available | NULL           |
+------+--------------------------------------+--------------------------------------+--------------+--------------------+--------------------------------------+---------------------+---------------+-----------+----------------+
3 rows in set (0.00 sec)
    ```
