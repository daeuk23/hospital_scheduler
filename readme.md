# veterinary hospital scheduler  
It is a project designed in C language to easily manage related information  
It is optimized for managing patient information and appointments.  

## Information  
Developed period : July 20th ~ Aug 3rd, 2023  
Contact : a24738598@gmail.com  

## Core Files  

- **Main**  
[Main.c](main.c) : Providing UI of options that manager could select  

- **Core**  
[Core.c](core.c) : A collection of `utility` functions that validate user input and process strings and phone numbers in a specified format.  
[Core.h](core.h) : Header file of `utility` functions.  

- **Clinic**  
[Clinic.c](clinic.c) : Key files that address input and storage for `patient` information and `appointments`.  
[Clinic.h](clinic.c) : Header file of these `patient` information and `appointments`.  

## Feature for users  

### Externaly handling data       
- **Import** data by txt file : import previous data easily  
- **View** data : Easily export data If needed  

### Program Feauture  
1. Patient Management  
- View, Searh, Add, Edit, Remove features are allowed  
2. Appointment Management  
- View based on criteria, Add, Remove appointments are allowed  

## How to run

### 1. Clone repo

Clone my repo to your local

```bash
git clone https://github.com/daeuk23/hospital_scheduler.git
cd veterinartHosp
```  

### 2. move textfile

File Integration for testing

```bash
mkdir -p veterinartHosp
mv Data_files/*.txt ..
```  

### 3. Compile In remote 
G++ compiler required  

```bash
g++ -Wall -std=c++17 -g -o main main.c clinic.c core.c
```
Using SSH will be good




