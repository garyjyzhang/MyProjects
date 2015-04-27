import urllib
import time

#This function returns a list of data
def get_data(symbol):

    #Store today's date in a string
    today = time.asctime(time.localtime())

    #The url at which the data can be found
    url = construct_url(symbol, today)

    #Read the data at the url into a variable
    response = urllib.urlopen(url).read()

    try:
        #This list holds the initially parsed data
        data = parse_rawdata(response)
    except:
        print("Invalid stock or not currently available from Google Finance")
        print("Please try again")
        return 0

    #This list holds the data that will be returned
    prices = refine_data(data, today)

    return prices

# Constructs the url where the data can be found
def construct_url(symbol, today):
    #Unpack the today string into usable variables
    month = today[4:7]
    day = today[8:10]
    year = today[20:24]
    lastyear = str(int(year) - 1)

    return "http://www.google.com/finance/historical?q=" + symbol + "&histperiod=daily&startdate=" \
           + month + "+" + day + "%2C+" + lastyear + "&enddate=" + month + "+" + day + "%2C+" + year + "&output=csv"
# Parse raw data into usable data
def parse_rawdata(response):
    #Set to 35 to skip the first junk line, hardcoded as this should never change
    i = 35
    data = []
    #The loop just goes until the end of the response string
    while 1 == 1:
        val = 0
        try:
            val = read_line(response, i)
        except:
            break

        line = val[0]
        i = val[1]

        val = parse_line(line)
        data.append(val)

    #Reverse the list to make life easier
    data.reverse()
    return data
# Reads a line from a large string variable
def read_line(response, index):
    line = ""
    #Read one character at a time until new line character is reached
    while response[index] != "\n":
        line += (response[index])
        index += 1
    #Add a new line character to make it easier to work with
    line += ("\n")
    index += 1
    return (line, index)
# Parse the useful information out of the line
def parse_line(line):
    i = 0
    day = ""
    month = ""
    year = "20" #The first 2 digits hardcoded in as we only go back 1 year
    close = ""
    #Parse the day from the string
    while line[i] != "-":
        day += line[i]
        i += 1
    i += 1

    #Parse the month from the string
    while line[i] != "-":
        month += line[i]
        i += 1
    i+= 1

    #Parse the year
    while line[i] != ",":
        year += line[i]
        i += 1
    i += 1

    #Parse the close price
    #This loop discards the day's high
    while line[i] != ",":
        i += 1
    i += 1
    #This loop discards the day's low
    while line[i] != ",":
        i += 1
    i += 1
    #This line reads the day's close
    while line[i] != ",":
        close += line[i]
        i += 1

    return (day, month, year, close)
# Refines the data parsed from the raw data into what will be used by the rest of the program
def refine_data(data, today):
    #Unpack the today string into usable variables
    month = today[4:7]
    day = str(int(today[8:10])) # in case the day string is 2 characters on a day with only 1 digit
    year = today[20:24]
    lastyear = str(int(year) - 1)

    prices = []

    #Date essentially acts as the index for the final prices list where the initial value given is the 0 index
    date = month + " " + day + " " + lastyear + "\n"

    #This gets the last day in the list that we have data for, not necessarily today with the current way the data is
    # fetched
    today = data[len(data) - 1][1] + " " + data[len(data) - 1][0] + " " + data[len(data) - 1][2] + "\n"
    tom = tomorrow(today)
    j = 0
    i = 0
    #While structs or lists would probably be easier, I use strings for the simple equality checks
    while date != tom:
        if date == (data[j][1] + " " + data[j][0] + " " + data[j][2] + "\n"):
            prices.append(data[j][3])
            j += 1
        else:
            prices.append(data[j][3])
        i += 1
        date = tomorrow(date)
    return prices
# Returns the day after the date given
def tomorrow(date):
    i = 0
    month = ""
    day = ""
    year = ""
    while date[i] != " ":
        month += date[i]
        i += 1
    i += 1
    while date[i] != " ":
        day += date[i]
        i += 1
    i += 1
    while date[i] != "\n":
        year += date[i]
        i += 1

    #Nothing but the day will ever change in this case
    if int(day) + 1 < 29:
        return month +  " " + str(int(day) + 1) + " " + year + "\n"
    if int(day) + 1 == 29:#Have to check if it's February and if it's a leap year
        if month != "Feb":#Return like the previous case
            return month +  " " + str(int(day) + 1) + " " + year + "\n"
        if is_leap(year):#Again, return like previous case
            return month +  " " + str(int(day) + 1) + " " + year + "\n"
        else: #is  Feb and is not a leap year so change the month to March
            return "Mar " + "1 " + year + "\n"
    if int(day) + 1 == 30:
        if(month != "Feb"):#Return like any other day
            return month +  " " + str(int(day) + 1) + " " + year + "\n"
        else:#It was a leap year and now it must be March
            return "Mar " + "1 " + year + "\n"
    if int(day) + 1 == 31:
        if month == "Jan":#Return like any other day for months with 31 days
            return month +  " " + str(int(day) + 1) + " " + year + "\n"
        if month == "Mar":
            return month +  " " + str(int(day) + 1) + " " + year + "\n"
        if month == "May":
            return month +  " " + str(int(day) + 1) + " " + year + "\n"
        if month == "Jul":
            return month +  " " + str(int(day) + 1) + " " + year + "\n"
        if month == "Aug":
            return month +  " " + str(int(day) + 1) + " " + year + "\n"
        if month == "Oct":
            return month +  " " + str(int(day) + 1) + " " + year + "\n"
        if month == "Dec":
            return month +  " " + str(int(day) + 1) + " " + year + "\n"
        if month == "Apr":#Must Increment months for months with 30 days
            return "May " + "1 " + year + "\n"
        if month == "Jun":
            return "Jul " + "1 " + year + "\n"
        if month == "Sep":
            return "Oct " + "1 " + year + "\n"
        if month == "Nov":
            return "Dec " + "1 " + year + "\n"
    if int(day) + 1 == 32:
        if month == "Jan":#Will always have to increment at least the month
            return "Feb " + "1 " + year + "\n"
        if month == "Mar":
            return "Apr " + "1 " + year + "\n"
        if month == "May":
            return "Jun " + "1 " + year + "\n"
        if month == "Jul":
            return "Aug " + "1 " + year + "\n"
        if month == "Aug":
            return "Sep " + "1 " + year + "\n"
        if month == "Oct":
            return "Nov " + "1 " + year + "\n"
        if month == "Dec": # Only case where the year will be incremented
            return "Jan " + "1 " + str(int(year) + 1) + "\n"
# A simple function for checking if a year is a leap year
def is_leap(year):
    year = int(year)
    if year % 400 == 0:
        return 1
    if year % 100 == 0:
        return 0
    if year % 4 == 0:
        return 1
    else:
        return 0