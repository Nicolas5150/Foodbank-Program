//  Created by Nicolas Emery on 10/1/14.
//  COP 3223 - 0002
//  Assignment 3 - (FoodBank.c)
//  Copyright (c) 2014 Nicolas Emery. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, const char * argv[])
{
    
    // Variables needed
    int option, DonQuant, found, i;
    int DonCount=0, ReqCount=0, DonAmt[100], ReqAmt[100];
    char word[20], DonInvType[100][20], ReqInvType[100][20];
    
    // Intro to program and its options to select from
    printf("*Welcome to the Food Bank Program*\n ");
    printf("1.Add a donation\n 2.Add a request\n 3.Fulfill a request\n 4.Print status report\n 5.Exit\n");
    printf("Enter your choice:");
    scanf("%d", &option);
    
    // Menu driven program with options 1-4 (6 or above causes loop to request val in range)
    while(option != 5)
        
    {
         // Option 1 - Add a donation
        if(option == 1)
        {
            // Ask user for donation type and quantity
            printf("\nDonation will now be made\n");
            printf("Enter inventory type:");
            scanf("%s", &word);
            printf("Enter the amount:");
            scanf("%d", &DonQuant);
            
            // If we find the word make found be the postion of the word
            found = -99;
            for(i=0; i<DonCount; i++)
            {
               if(strcmp(DonInvType[i], word) == 0)
                   found =i;
            }
            // If word isnt found - Copy word into Inventory then set the amount of donation
            if(found == -99)
            {
                strcpy(DonInvType[i], word);
                DonAmt[i] = DonQuant;
                // Move donation counter (the number on the side of the list (visually) up one)
                DonCount ++;
            }
            else
            {
                DonAmt[found] += DonQuant;
            }
            printf("Donation added!\n");
        }
        
         // Option 2 - Request a donation
        if(option == 2)
        {
            // Ask user for donation type and quantity
            printf("\nRequest will now be made\n");
            printf("Enter inventory type:");
            scanf("%s", &word);
            printf("Enter the amount:");
            scanf("%d", &DonQuant);
            
            // If we find the word make found be the postion of the word
            found = -99;
            for(i=0; i<ReqCount; i++)
            {
                if(strcmp(ReqInvType[i], word) == 0)
                    found =i;
            }
            // If word isnt found - Copy word into Inventory then set the amount of donation
            if(found == -99)
            {
                strcpy(ReqInvType[i], word);
                ReqAmt[i] = DonQuant;
                // Move donation counter (the number on the side of the list (visually) up one)
                ReqCount ++;
            }
            else
            {
                ReqAmt[found] += DonQuant;
            }
            printf("Request added!\n");
        }

        // Option 3 - Fulfill a request
        if(option == 3)
        {
            printf("\n----Fulfilling Requests----\n");
            // Message 1 - No requests yet
            if(ReqCount == 0)
            {
                printf("No requests have been made yet.\n");
            }
            // Message 2 - No donations yet
            else if (DonCount == 0)
            {
                printf("No donations have been made yet.\n");
            }
            // Trying to find item in list / array
            else
            {
                found = -99;
                for(i=0; i<DonCount; i++)
                {
                    if(strcmp(DonInvType[i],ReqInvType[0]) == 0)
                        found =i;
                }
                if(found == -99)
                    // Message 3 - No Match
                {
                    printf("Request does not have a match in the donations yet.\n");
                }
                // The item has been found and will now try to be fulfilled
                else
                {
                    printf("We have the donation but it must be tested for quantity.\n");
                    // Donated amount equals requested amount
                    if(DonAmt[found] == ReqAmt[0])
                    {
                        // Message 4 - Match (exact)
                        printf("Your request will be satisfied; full donation value used.\n");
                        // Delete the request from the list / array (by shifting list up one)
                        for(i=1; i<ReqCount; i++)
                        {
                            // Move item and its value to the place holder of i-1 (one up)
                            strcpy(ReqInvType[i-1], ReqInvType[i]);
                            ReqAmt[i-1] = ReqAmt[i];
                        }
                        ReqCount --;
                        // Lower the counter after entry is lost
                        for(i=found; i<DonCount -1; i++)
                        {
                            strcpy(DonInvType[i], DonInvType[i+1]);
                            DonAmt[i]= DonAmt[i+1];
                        }
                        DonCount --;
                    }
                    else if (DonAmt[found]>ReqAmt[0])
                    {
                        // Remove the amount of item by requested amount
                        DonAmt[found] -= ReqAmt[0];
                        for(i=1; i<ReqCount; i++)
                        {
                            strcpy(ReqInvType[i-1], ReqInvType[i]);
                            // Lower the value into a higher position
                            ReqAmt[i-1] = ReqAmt[i];
                        }
                        ReqCount --;
                        // Message 4 - Match (request smaller than total)
                        printf("Your request has been fulfilled.\n");
                    }
                    // Reduce donation and request
                    else
                    {
                        ReqAmt[0] -= DonAmt[found];
                        for(i=found; i<DonCount -1; i++)
                        {
                            strcpy(DonInvType[i], DonInvType[i+1]);
                            DonAmt[i] = DonAmt[i+1];
                        }
                        DonCount --;
                        // Message 4 - Match (request smaller than total)
                        printf("Request has partially fulfilled.\n");
                    }
                }
            }
        }
        
        // Option 4 - Print status report
        if(option == 4)
        {
            // Print the donation table words and values
            printf("\n--------Donations--------\n");
            for(i=0; i<DonCount; i++)
            {
                printf("~ %s", DonInvType[i]);
                printf(" %d\n", DonAmt[i]);
            }
            // Print the request table words and values
            printf("\n--------Requests--------\n");
            for(i=0; i<ReqCount; i++)
            {
                printf("~ %s", ReqInvType[i]);
                printf(" %d\n", ReqAmt[i]);
            }
        }
        
        // Option Other - for any value not between 1 - 5
        if (option >= 6)
        {
            printf("\nThe value you have entered is not valid, program will now repromt.\n");
        }
        
        // Repromt the menu until otherwise (5 is entered)
        printf("\n*Welcome to the Food Bank Program*\n ");
        printf("1.Add a donation\n 2.Add a request\n 3.Fulfill a request\n 4.Print status report\n 5.Exit\n");
        printf("Enter your choice:");
        scanf("%d", &option);
    }
    
    // Option 5 - Exit the program
    if (option == 5)
    {
        printf("\nThank you for using the FoodBank; program will now end\n");
    }
    system ("PAUSE");
    return 0;
}
