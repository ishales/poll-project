//
//  main.cpp
//  project 3
//
//  Created by Isabelle Hales on 10/19/22.
//  Copyright © 2022 CS31. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

// Return true if the argument is a two-uppercase-letter state code, or false otherwise
bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
        "LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
        "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

//check whether each stateForecase meets the requirements
bool isValidStateForecast(string stateForecast){
    int sfValue = 0;
    //empty string is valid state forecast
    if(stateForecast == ""){
        sfValue = 1;
    }
    
    //check whether first two characters of stateForecast are a stateCode
    int sfIndex = 0;
    int sfSize = stateForecast.length();
    string stateCode = "";
    
    if(!isalpha(stateForecast.at(0))){
            sfValue = 0;
    } else {
        toupper(stateForecast.at(0));
        stateCode += stateForecast.at(0);
        }

    if(!isalpha(stateForecast.at(1))){
        sfValue = 0;
        return sfValue;
    } else {
        toupper(stateForecast.at(1));
        stateCode += stateForecast.at(1);
        }
        
    if(!isValidUppercaseStateCode(stateCode)){
        sfValue = 0;
        return sfValue;
        }
    
    //check for party results
    for(sfIndex = 2; sfIndex < sfSize; sfIndex++){
        if(sfIndex == sfSize - 1){
            if(isalpha(stateForecast.at(sfIndex)) && isdigit(stateForecast.at(sfIndex - 1))){
            sfValue = 1;
            } }
        else if(isdigit(stateForecast.at(sfIndex))){
            
            //case 1 = 1 digit w party character
            if(isalpha(stateForecast.at(sfIndex + 1))){
                sfValue = 1;
            }
            //case 2 = 2 digits w party character
            else if(isdigit(stateForecast.at(sfIndex+1))){
                if(stateForecast.at(sfIndex+2 == sfSize - 2)){
                    sfValue = 0;
                } else {
                    if(isalpha(stateForecast.at(sfIndex+2))){
                        sfValue = 1;
                    }
                }
            }
            else {
                sfValue = 0;
            }
        }
    }
    return sfValue;
}

//returns true if poll data string meets requirements
bool isValidPollString(string pollData) {
    int psValue = 0;
    //empty string is valid poll string
    if(pollData == ""){
        psValue = 1;
    }
    
    //separate poll string into separate state forecasts
    int index = 0;
    int size = pollData.length();
    string stateForecast = "";
    for(index = 0; index < size; index++){
        if(pollData.at(index) == ','){
            if(!isValidStateForecast(stateForecast)){
                psValue = 0;
            }
            else{
                stateForecast = "";
            }
        } else {
            stateForecast += pollData.at(index);
        }
        if(index == size - 1){
            if(isValidStateForecast(stateForecast)){
               psValue = 1;
            } else{
                psValue = 0;
            }
        }
        }
    return psValue;
}


//interpret the poll results
int countSeats(string pollData, char party, int& seatCount) {
    int csValue = 0;
    int total = 0;
    
    //If the parameter pollData is not a poll data string, this function returns 1
    if(!isValidPollString(pollData)){
        csValue = 1;
        return csValue;
    }
    
    //If the parameter party is not a letter, this function returns 2
    if(!isalpha(party)){
        csValue = 2;
        return csValue;
    }
    
    //scan the poll data string to count the number of seats
    int size = pollData.size();
    int digit = 1;
    
    for(int i = 0; i < size; i++){
        if(pollData.at(i) == toupper(party) || pollData.at(i) == tolower(party)){
            int j = i - 1;
            while(isdigit(pollData.at(j))){
                int temp = (pollData.at(j)) - '0';
                total += temp * digit;
                j--;
                digit *= 10;
            }
            digit = 1;
        }
    }
    
    seatCount = total;
    
    return csValue;
}

//main function
int main()
{
    assert(isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D"));
    assert(!isValidPollString("ca"));
    int seats;
    seats = -999;    // so we can detect whether countSeats sets seats
    assert(countSeats("ca", 'd', seats) == 1 && seats == -999);
    seats = -999;    // so we can detect whether countSeats changes seats
    assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", '%', seats) == 2  &&  seats == -999);
    cerr << "All tests succeeded" << endl;
}



