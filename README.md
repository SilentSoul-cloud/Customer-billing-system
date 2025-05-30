# Customer Billing System

A C-based command-line application to manage mobile customer billing. This program allows users to add, view, update, and delete customer records, with persistent file storage and optional CSV export.

## Features

* Add new customer records (name, phone, mobile usage)
* Prevent duplicate phone numbers
* Sort and list customers alphabetically
* Update mobile usage and phone number
* Update call rate globally
* Delete customer records with confirmation
* View details of a single customer
* Export all records to `customers.csv`
* Save/load customer data to/from `Customers.txt`
* Maintain log of system actions in `logData.txt`

## File Overview

* `billing_system.c` — Main source code
* `Customers.txt` — Persistent data file
* `customers.csv` — CSV export file
* `logData.txt` — Event log file

## How to Compile and Run

```bash
gcc -o billing billing_system.c
./billing
```

## Author

Created by **SilentSoul-cloud (Arka Saha)**
May 2025
Feel free to use or modify with proper attribution.
