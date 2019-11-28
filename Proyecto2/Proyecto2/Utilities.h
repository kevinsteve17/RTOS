/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Utilities.h
 * Author: kevin
 *
 * Created on November 25, 2019, 8:43 PM
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#ifdef __cplusplus
extern "C" {
#endif

    
    int gcd(int a, int b)
    {
        while(b>0)
        {
            int temp =  b;
            b = a % b; 
            a = temp; 
        }
        
        return a;
    }
    
    int lcm(int a, int b)
    {
        return a * (b/gcd(a,b));
    }
    
    int LCM(int* input, int inputCount)
    {
        int result = input[0];
        for (int i = 0; i < inputCount; i++) 
        {
            if (result != 0 && input[i] != 0) 
            {
                result = lcm(result, input[i]);
            }
        }
        return result;
    }


#ifdef __cplusplus
}
#endif

#endif /* UTILITIES_H */

