#include "settings.h"          // Include header for settings function declarations
#include "lcd_defines.h"       // Include LCD related definitions/macros
#include "lcd.h"               // Include LCD interface functions
#include "delay.h"             // Include delay functions
#include "types.h"             // Include common type definitions like u8, s8, u32, etc.
#include "kpm.h"               // Include keypad module functions
#include <lpc21xx.h>           // Include LPC21xx MCU register definitions
#include <stdlib.h>            // Include standard library functions (if needed)

u32 PSW=1234;                    // Define default admin password as 1234
s32 UserPSW;                  // Variable to store user-entered password
u8 choice;                    // Variable to hold user menu choice
extern u32 msg_flag;          // External flag indicating if message display is enabled

// Define a structure to hold message info including time and enable status
typedef struct 
{
	u8 hour;                   // Hour at which message should be displayed
	u8 minute;                 // Minute at which message should be displayed
	char text[80];             // Message text (max 80 chars)
	u8 enabled;                // Flag: 1 = message enabled, 0 = disabled/skipped
} Message;

extern Message messageList[10];   // External array of 10 messages
extern s8 hour,min,sec,dom,month,year,dow;  // External date/time variables

// Main function to handle the settings menu
void settings()
{
	u8 flag=1;                 // Local flag to control while loop continuation
	CmdLCD(CLEAR_LCD);         // Clear LCD screen
	StrLCD("  ADMIN ");         // Print "ADMIN " on first line of LCD
	CmdLCD(GOTO_LINE2_POS0);   // Move cursor to beginning of second line
	StrLCD("        MODE");     // Print "MODE" with padding on second line
	delay_s(2);                // Wait for 2 seconds before proceeding

b:  CmdLCD(CLEAR_LCD);         // Clear LCD for password prompt
    StrLCD("ENTER PASSWORD");  // Prompt user to enter password

	UserPSW = ReadNum2(10);     // Read numeric input of max 10 digits from keypad

	if(UserPSW==-1)             // If input is invalid (e.g., timeout or cancel)
	{
		CmdLCD(CLEAR_LCD);      // Clear LCD
		StrLCD("INVALID");      // Show invalid input message
		delay_s(2);             // Delay 2 seconds before retry
		goto b;                 // Jump back to password prompt
	}

	if(UserPSW==PSW)            // If entered password matches stored password
	{
		while(1)                // Enter infinite loop until user exits admin menu
		{
a:	    CmdLCD(CLEAR_LCD);          // Clear LCD before menu display
		    CmdLCD(GOTO_LINE1_POS0);  // Move cursor to first line start
		    StrLCD("1.Time 2.Date");   // Display first line of menu options
		    CmdLCD(GOTO_LINE2_POS0);  // Move cursor to second line start
		    StrLCD("3.day 4.Msg 5.Ex"); // Display second line of menu options
		    choice = Keyscan();        // Scan for user key press

		    switch(choice)             // Branch based on user selection
		    {
			    case '1': Edit_time(); break;   // Option 1: Call time edit function
			    case '2': Edit_date(); break;   // Option 2: Call date edit function
			    case '3': DOW = Edit_day(); break; // Option 3: Edit day of week, save to DOW
			    case '4': MsgDisp(); break;     // Option 4: Display/enable/disable messages
			    case '5': flag=0; break;        // Option 5: Exit admin menu (flag=0)
			    default : 
			        CmdLCD(CLEAR_LCD);          // Invalid input: clear LCD
			        StrLCD("Invalid input");   // Show invalid message
			        delay_s(2);                // Wait 2 seconds
			        goto a;                    // Redisplay admin menu options
		    }
		    if(flag==0) break;  // If exit option chosen, break while loop
		}
	}
	else                         // If password does not match stored PSW
	{
		CmdLCD(CLEAR_LCD);        // Clear LCD
		StrLCD("INVALID PASSWORD"); // Show invalid password message
		delay_s(2);               // Wait 2 seconds
		goto b;                   // Return to password entry prompt
	}
}

// Function to handle editing of time values (hour, min, sec)
void Edit_time()
{
	while(1)                   // Repeat until user chooses to go back
	{
		u8 ch,flag=1;          // Local choice and flag variables
		CmdLCD(CLEAR_LCD);     // Clear LCD before showing menu
		StrLCD("1.Hr 2.Min 3.Sec"); // Show time edit options line 1
		CmdLCD(GOTO_LINE2_POS0);// Move to second line start
		StrLCD("4.Back");       // Show option to go back
		ch=Keyscan();           // Scan user key input

		switch(ch)              // Handle user choice
		{
			case '1': HOUR = Edit_hour(); break;  // Edit hour
			case '2': MIN  = Edit_min(); break;   // Edit minutes
			case '3': SEC  = Edit_sec(); break;   // Edit seconds
			case '4': flag=0; break;               // Back option, set flag to 0
			default : 
				StrLCD("  Invalid");             // Show invalid input message
				delay_s(2);                     // Wait 2 seconds
		}
		if(flag==0) break;         // Exit loop if back chosen
	}
}

// Function to edit hour value between 0 and 23
s8 Edit_hour()
{
	s32 h;                       // Variable to hold hour input
	while(1)
	{
		CmdLCD(CLEAR_LCD);       // Clear LCD for input prompt
		StrLCD("ENTER HOUR(0-23)"); // Prompt user to enter hour
		CmdLCD(GOTO_LINE2_POS0); // Move to second line
		h=ReadNum2(2);           // Read 2-digit number input

		if(h==-1 || h>23)        // If input invalid or out of range
		{
			StrLCD("  Invalid"); // Show invalid message
			delay_s(2);          // Wait 2 seconds
		}
		else 
		{
			return h;             // Valid input, return hour value
		}
	}
}

// Function to edit minute value between 0 and 59
s8 Edit_min()
{
	s32 m;                      // Variable for minutes input
	while(1)
	{
		CmdLCD(CLEAR_LCD);      // Clear LCD screen
		StrLCD("ENTER Mins(0-59)"); // Prompt for minutes input
		CmdLCD(GOTO_LINE2_POS0);// Move cursor to second line
		m=ReadNum2(2);          // Read 2-digit input

		if(m==-1 || m>59)       // Invalid or out of range input check
		{
			StrLCD(" Invalid"); // Show invalid message
			delay_s(2);         // Wait 2 seconds
		}
		else
		{
			return m;            // Return valid minute input
		}
	}
}

// Function to edit seconds value between 0 and 59
s8 Edit_sec()
{
	s32 s;                      // Variable for seconds input
	while(1)
	{
		CmdLCD(CLEAR_LCD);      // Clear LCD before prompt
		StrLCD("Enter secs(0-59)"); // Prompt for seconds
		CmdLCD(GOTO_LINE2_POS0);// Move cursor to second line
		s=ReadNum2(2);          // Read input

		if(s==-1 || s>59)       // Validate input
		{
			StrLCD("  Invalid"); // Show invalid message
			delay_s(2);          // Wait 2 seconds
		}
		else
		{
			return s;            // Return valid seconds
		}
	}
}

// Function to show date edit menu and handle options
void Edit_date()
{
	s8 choice,flag=1;           // Choice for menu option and flag for loop control

	while(1)
	{
		CmdLCD(CLEAR_LCD);      // Clear LCD screen
		StrLCD("1.Date 2.Month"); // Show first line options
		CmdLCD(GOTO_LINE2_POS0);// Move to second line
		StrLCD("3.Year 4.Back"); // Show second line options
		choice=Keyscan();       // Get user choice from keypad

		switch(choice)
		{
			case '1': DOM = Edit_Ndate(); break;   // Edit day of month
			case '2': MONTH = Edit_month(); break; // Edit month
			case '3': YEAR = Edit_year(); break;   // Edit year
			case '4': flag=0; break;                // Exit loop/back option
			default : 
				CmdLCD(CLEAR_LCD);
				StrLCD(" Invalid ");              // Show invalid choice
				delay_s(2);                     // Wait 2 seconds
		}
		if(flag==0)
			break;               // Break loop if back option selected
	}
}

// Function to edit day of month (1 to 31)
s8 Edit_Ndate()
{
	s32 d;                      // Variable to hold date input
	while(1)
	{
		CmdLCD(CLEAR_LCD);      // Clear LCD screen
		StrLCD("ENTER DATE(1-31)"); // Prompt user for date input
		d=ReadNum2(2);          // Read input (max 2 digits)

		if(d==-1 || d==0 || d>31) // Validate input range
		{
			StrLCD("  Invalid"); // Show invalid input message
			delay_s(2);          // Wait 2 seconds
		}
		else
		{
			return d;            // Return valid date value
		}
	}
}

// Function to edit month value (1 to 12)
s8 Edit_month()
{
	s32 m;                      // Variable to hold month input
	while(1)
	{
		CmdLCD(CLEAR_LCD);      // Clear screen before prompt
		StrLCD("ENTER MONTH:1-12"); // Prompt user for month
		m=ReadNum2(2);          // Read 2-digit input

		if(m==-1 || m==0 || m>12) // Validate input
		{
			StrLCD("   Invalid"); // Show invalid message
			delay_s(2);          // Delay 2 seconds
		}
		else
		{
			return m;            // Return valid month
		}
	}
}

// Function to edit the year value, expects input between 2025 and 2999
s32 Edit_year()
{
    s32 y;  // Variable to store the input year

    while(1) // Loop until valid input is received
    {
        CmdLCD(CLEAR_LCD);                // Clear the LCD screen
        StrLCD("ENTER (2025-2999)");     // Prompt user to enter a year in this range

        y = ReadNum2(4);                 // Read up to 4-digit number input from keypad

        if(y == -1)                     // If input is invalid (e.g., non-numeric or canceled)
        {
            StrLCD("  Invalid");         // Display "Invalid" message
            delay_s(2);                  // Wait for 2 seconds
        }
        else if(y < 2025 || y > 2999)   // If input is out of acceptable range
        {
            StrLCD("   Invalid");        // Display "Invalid" message
            delay_s(2);                  // Wait for 2 seconds
        }
        else
        {
            return y;                    // Return the valid year input and exit function
        }
    }
}

// Function to edit/set the day of the week (0=Sunday to 6=Saturday)
s8 Edit_day()
{
    s8 d;  // Variable to store the day input

    while(1) // Loop until a valid day is selected
    {
        CmdLCD(CLEAR_LCD);              // Clear the LCD screen
        StrLCD("0.Su 1.M 2.T 3.W");    // Display options for days (Sunday to Wednesday)
        CmdLCD(GOTO_LINE2_POS0);        // Move cursor to the beginning of second line
        StrLCD("4.Th 5.Fr 6.Sa7E");    // Display options for days (Thursday to Saturday) and exit option '7E'

        d = Keyscan() - 48;             // Read a key from keypad and convert ASCII to integer (subtract '0' = 48)

        if(d > 6)                      // If entered value is invalid (greater than 6)
        {
            CmdLCD(CLEAR_LCD);          // Clear LCD
            StrLCD("Invalid");          // Show invalid message
            delay_s(2);                 // Wait for 2 seconds
        }
        else
        {
            return d;                   // Return valid day number and exit function
        }
    }
}

// Function to display and enable/disable stored messages by their index number (1-10)
void MsgDisp()
{
    s32 ch, n;      // Variables for message number and user choice
    while(1)        // Loop to allow repeated message selection and modification
    {
        u8 flag = 1;  // Flag to control inner loop exit

    a:  // Label for goto, to repeat input on invalid entry
        CmdLCD(CLEAR_LCD);          // Clear LCD screen
        StrLCD("Enter Num:1-10");   // Prompt user to enter message number between 1 and 10

        ch = ReadNum2(2);           // Read up to 2 digit number from keypad

        if(ch <= 0 || ch > 10)      // Validate message number range
        {
            StrLCD(" Invalid");      // Display invalid message prompt
            delay_s(2);             // Wait 2 seconds
            goto a;                 // Repeat input prompt
        }

        //delay_ms(500);             // (Commented out) Short delay before next prompt
        CmdLCD(CLEAR_LCD);          // Clear LCD for next message
        StrLCD("1.Enable 2.Disable");// Prompt user to enable or disable the selected message

        n = Keyscan();              // Read user choice for enable/disable

        switch(n)
        {
            case '1':   // Enable the message
                messageList[ch - 1].enabled = 1; // Set enable flag for selected message (index adjusted)
                msg_flag = 1;                   // Set global message flag to indicate change
                flag = 0;                      // Reset flag to break loop
                CmdLCD(GOTO_LINE2_POS0);       // Move cursor to 2nd line start
                StrLCD("Enabled");             // Show confirmation
                delay_ms(500);                 // Delay for half a second
                break;

            case '2':   // Disable the message
                messageList[ch - 1].enabled = 0; // Clear enable flag for message
                msg_flag = 0;                   // Reset global message flag
                flag = 0;                      // Reset flag to break loop
                CmdLCD(GOTO_LINE2_POS0);       // Move cursor to 2nd line start
                StrLCD("Disabled");            // Show confirmation
                delay_ms(500);                 // Delay for half a second
                break;

            default:    // Handle invalid choice input
                StrLCD("Invalid");            // Display invalid message prompt
                delay_s(2);                   // Wait 2 seconds
        }

        if(flag == 0)   // If flag reset, break out of the loop
            break;
    }
}
