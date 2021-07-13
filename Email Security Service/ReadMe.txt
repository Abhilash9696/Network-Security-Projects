

This program allows us to create public and private key pairs of users listed in a text file and then provide various email security features for exchange of email messages between the users.
-------------------------------------------------CreateKeys------------------------------------
You can create public and private key pairs for a list of users using the following command
py Lab2-cs20m006.py CreateKeys UserNameListFile.txt 2048
py Lab2-cs20m006.py CreateKeys UserNameListFile.txt 1024

The email security system provides three types of security.
1. Confidentiality only(CONF).
2. Authentication only(AUIN).
3. Confidentiality and Authentication(COAI).

The commands to implement respective security service needed are as shown below.
-------------------CONF--------------------
py Lab2-cs20m006.py CreateMail CONF Abhilash Anil EmailInputFile.txt EmailOutputFile.txt sha512 aes-256-cbc 2048


py Lab2-cs20m006.py ReadMail CONF Abhilash Anil EmailOutputFile.txt Plaintext.txt sha512 aes-256-cbc 2048

py Lab2-cs20m006.py CreateMail CONF Abhilash Anil EmailInputFile.txt EmailOutputFile.txt sha512 des-ede3-cbc 2048

py Lab2-cs20m006.py ReadMail CONF Abhilash Anil EmailOutputFile.txt Plaintext.txt sha512 des-ede3-cbc 2048

py Lab2-cs20m006.py CreateMail CONF Abhilash Anil EmailInputFile.txt EmailOutputFile.txt sha3-512 aes-256-cbc 2048

py Lab2-cs20m006.py ReadMail CONF Abhilash Anil EmailOutputFile.txt Plaintext.txt sha3-512 aes-256-cbc 2048

py Lab2-cs20m006.py CreateMail CONF Abhilash Anil EmailInputFile.txt EmailOutputFile.txt sha3-512 des-ede3-cbc 2048

py Lab2-cs20m006.py ReadMail CONF Abhilash Anil EmailOutputFile.txt Plaintext.txt sha3-512 des-ede3-cbc 2048

-------------------AUIN--------------------
py Lab2-cs20m006.py CreateMail AUIN Abhilash Anil EmailInputFile.txt EmailOutputFile.txt sha512 aes-256-cbc 2048

py Lab2-cs20m006.py ReadMail AUIN Abhilash Anil EmailOutputFile.txt Plaintext.txt sha512 aes-256-cbc 2048

py Lab2-cs20m006.py CreateMail AUIN Abhilash Anil EmailInputFile.txt EmailOutputFile.txt sha512 des-ede3-cbc 2048

py Lab2-cs20m006.py ReadMail AUIN Abhilash Anil EmailOutputFile.txt Plaintext.txt sha512 des-ede3-cbc 2048

py Lab2-cs20m006.py CreateMail AUIN Abhilash Anil EmailInputFile.txt EmailOutputFile.txt sha3-512 aes-256-cbc 2048

py Lab2-cs20m006.py ReadMail AUIN Abhilash Anil EmailOutputFile.txt Plaintext.txt sha3-512 aes-256-cbc 2048

py Lab2-cs20m006.py CreateMail AUIN Abhilash Anil EmailInputFile.txt EmailOutputFile.txt sha3-512 des-ede3-cbc 2048

py Lab2-cs20m006.py ReadMail AUIN Abhilash Anil EmailOutputFile.txt Plaintext.txt sha3-512 des-ede3-cbc 2048

----------------------COAI----------------------------

py Lab2-cs20m006.py CreateMail COAI Abhilash Anil EmailInputFile.txt EmailOutputFile.txt sha512 aes-256-cbc 2048

py Lab2-cs20m006.py ReadMail COAI Abhilash Anil EmailOutputFile.txt Plaintext.txt sha512 aes-256-cbc 2048

py Lab2-cs20m006.py CreateMail COAI Abhilash Anil EmailInputFile.txt EmailOutputFile.txt sha512 des-ede3-cbc 2048

py Lab2-cs20m006.py ReadMail COAI Abhilash Anil EmailOutputFile.txt Plaintext.txt sha512 des-ede3-cbc 2048

py Lab2-cs20m006.py CreateMail COAI Abhilash Anil EmailInputFile.txt EmailOutputFile.txt sha3-512 aes-256-cbc 2048

py Lab2-cs20m006.py ReadMail COAI Abhilash Anil EmailOutputFile.txt Plaintext.txt sha3-512 aes-256-cbc 2048

py Lab2-cs20m006.py CreateMail COAI Abhilash Anil EmailInputFile.txt EmailOutputFile.txt sha3-512 des-ede3-cbc 2048

py Lab2-cs20m006.py ReadMail COAI Abhilash Anil EmailOutputFile.txt Plaintext.txt sha3-512 des-ede3-cbc 2048


Note : READ ASSIGNMENT2.PDF for detailed desription.








