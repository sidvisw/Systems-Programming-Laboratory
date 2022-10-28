#!/usr/bin/gawk -f
BEGIN{
	# Assign the separator for the AWK
	FS=":"
	# Empty string to hold the output
	account=""
	# Initialize the current balance to 0
	balance=0
	# Initialize the current interest to 0
	interest=0.0
	# Boolean variable to check if new transactions are there or not
	foundNewTransactions=0
	# Assign the rate of interest per day for ordinary year
	rateForOrdinaryYear=5.0/365
	# Assign the rate of interest per day for leap year
	rateForLeapYear=5.0/366
	# Assign the number of days in each month along with the name of the months
	monthDays[1]=31;monthName[1]="January";
	monthDays[2]=28;monthName[2]="February";
	monthDays[3]=31;monthName[3]="March";
	monthDays[4]=30;monthName[4]="April";
	monthDays[5]=31;monthName[5]="May";
	monthDays[6]=30;monthName[6]="June";
	monthDays[7]=31;monthName[7]="July";
	monthDays[8]=31;monthName[8]="August";
	monthDays[9]=30;monthName[9]="September";
	monthDays[10]=31;monthName[10]="October";
	monthDays[11]=30;monthName[11]="November";
	monthDays[12]=31;monthName[12]="December";
}

# Function to check if the given date lies in a leap year or not
# Parameters: the date in the format dd-mm-yyyy
# Returns: 1 if the date is in a leap year, 0 otherwise
function isLeapYear(date){
	n=split(date,Date,"-")
	if(int(Date[3])%4==0 && int(Date[3])%100!=0 || int(Date[3])%400==0){
		return 1
	}
	return 0
}

# Function to fing the number of days between two given dates
# Parameters: the two dates in the format dd-mm-yyyy
# Returns: the number of days between the two dates
function daysBetweenDates(date1,date2){
	n=split(date1,Date1,"-")
	m=split(date2,Date2,"-")
	if(Date1[2]==Date2[2]){
		return int(Date2[1])-int(Date1[1])
	}
	else{
		if(isLeapYear(date1)==1){
			monthDays[2]=29
		}
		else{
			monthDays[2]=28
		}
		return monthDays[int(Date1[2])]+int(Date2[1])-int(Date1[1])
	}
}

# Function to determine if there is a change of year in the two given dates
# Parameters: the two dates in the format dd-mm-yyyy
# Returns: 1 if there is a change of year, 0 otherwise
function changeOfYear(date1,date2){
	n=split(date1,DATE1,"-")
	m=split(date2,DATE2,"-")
	if(DATE1[3]!=DATE2[3]){
		return 1;
	}
	return 0;
}

# The main block of code performing the required task
{
	# Check if the current line is a new account
	if($5=="ACCOUNT OPENED"){
		prevdate=$1
	}
	# Check if there is a new transaction 
	if($4 == "" && $5!="ACCOUNT OPENED"){
		# Check if the current line is a first new account
		if(foundNewTransactions==0){
			foundNewTransactions=1
			# Print "New transactions found" and the current balance
			print "+++ New transactions found"
			print "Last balance = " int(balance)
		}
		# Check if the current transaction is a credit transaction
		if($2!=""){
			split($1,DATE,"-")
			# Chbeck if there is a change of year
			if(changeOfYear(prevdate,$1)==1){
				# If there is a change of year, then calculate the interest and add interest to the account balance.
				split(prevdate,DATE1,"-")
				n1=31-int(DATE1[1])
				if(isLeapYear(prevdate)==1){
					interest+=balance*n1*rateForLeapYear/100
				}
				else{
					interest+=balance*n1*rateForOrdinaryYear/100
				}
				# Correspondingly update the account.txt file and update the balance
				balance+=interest
				account=account "31-12-" DATE1[3] ":" int(interest+0.5) "::" int(balance) ":INTEREST\n"
				printf("%-25s %-40s %-20s\n","December 31, " DATE1[3],"Credit of " int(interest+0.5) " for INTEREST","Balance = " int(balance))
				# Update the interest to 0
				interest=0
			}
			else{
				# If there is no change of year, then calculate the interest and print the transaction in the ouput.
				n1=daysBetweenDates(prevdate,$1)
				if(isLeapYear(prevdate)==1){
					interest+=balance*n1*rateForLeapYear/100
				}
				else{
					interest+=balance*n1*rateForOrdinaryYear/100
				}
			}
			# Correspondingly update the account.txt file and update the balance
			balance+=int($2)
			account=account $1 ":" $2 ":" $3 ":" int(balance) ":" $5 "\n"
			printf("%-25s %-40s %-20s\n",monthName[int(DATE[2])] " " DATE[1] ", " DATE[3],"Credit of " $2 " for " $5,"Balance = " int(balance))
		}
		# Check if the current transaction is a debit transaction
		else if($3!=""){
			split($1,DATE,"-")
			# Check if there is a change of year
			if(changeOfYear(prevdate,$1)==1){
				# If there is a change of year, then calculate the interest and add interest to the account balance.
				split(prevdate,DATE1,"-")
				n1=31-int(DATE1[1])
				if(isLeapYear(prevdate)==1){
					interest+=balance*n1*rateForLeapYear/100
				}
				else{
					interest+=balance*n1*rateForOrdinaryYear/100
				}
				# Correspondingly update the account.txt file and update the balance
				balance+=interest
				account=account "31-12-" DATE1[3] ":" int(interest+0.5) "::" int(balance) ":INTEREST\n"
				printf("%-25s %-40s %-20s\n","December 31, " DATE1[3],"Credit of " int(interest+0.5) " for INTEREST","Balance = " int(balance))
				# Update the interest to 0
				interest=0
			}
			else{
				# If there is no change of year, then calculate the interest and print the transaction in the ouput.
				n1=daysBetweenDates(prevdate,$1)
				if(isLeapYear(prevdate)==1){
					interest+=balance*n1*rateForLeapYear/100
				}
				else{
					interest+=balance*n1*rateForOrdinaryYear/100
				}
			}
			# Correspondingly update the account.txt file and update the balance
			balance-=int($3)
			account=account $1 ":" $2 ":" $3 ":" int(balance) ":" $5 "\n"
			printf("%-25s %-40s %-20s\n",monthName[int(DATE[2])] " " DATE[1] ", " DATE[3],"Debit of " $3 " for " $5,"Balance = " int(balance))
		}
		prevdate=$1
	}
	else{
		# If the current line is not a new transaction, then update the balance and interest
		account=account $0 "\n"
		# Correspondingly update the interest and update the balance
		# Check if the current transaction is a credit transaction
		if($2!=""){
			# Check if there is a change of year
			if(changeOfYear(prevdate,$1)==1){
				# If there is a change of year, then calculate the interest and add interest to the account balance.
				split(prevdate,DATE1,"-")
				n1=31-int(DATE1[1])
				if(isLeapYear(prevdate)==1){
					interest+=balance*n1*rateForLeapYear/100
				}
				else{
					interest+=balance*n1*rateForOrdinaryYear/100
				}
				# Correspondingly update the balance
				balance+=interest
				# Update the interest to 0
				interest=0
			}
			else{
				# If there is no change of year, then calculate the interest.
				split($1,DATE,"-")
				n1=daysBetweenDates(prevdate,$1)
				if(isLeapYear(prevdate)==1){
					interest+=balance*n1*rateForLeapYear/100
				}
				else{
					interest+=balance*n1*rateForOrdinaryYear/100
				}
			}
		}
		# Check if the current transaction is a debit transaction
		else if($3!=""){
			# Check if there is a change of year
			if(changeOfYear(prevdate,$1)==1){
				split(prevdate,DATE1,"-")
				n1=31-int(DATE1[1])
				if(isLeapYear(prevdate)==1){
					interest+=balance*n1*rateForLeapYear/100
				}
				else{
					interest+=balance*n1*rateForOrdinaryYear/100
				}
				# Correspondingly update the balance
				balance+=interest
				# Update the interest to 0
				interest=0
			}
			# If there is no change of year, then calculate the interest.
			else{
				split($1,DATE,"-")
				n1=daysBetweenDates(prevdate,$1)
				if(isLeapYear(prevdate)==1){
					interest+=balance*n1*rateForLeapYear/100
				}
				else{
					interest+=balance*n1*rateForOrdinaryYear/100
				}
			}
		}
		# Update the balance
		balance=int($4)
		prevdate=$1
	}
}
END{
	if(foundNewTransactions==0){
		print "+++ No new transactions found"
	}
	print "+++ Interest of this year up to the last transaction = " int(interest+0.5)
	printf("%s",account) > "account.txt"
}