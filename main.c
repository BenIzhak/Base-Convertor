#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SPBufferset.h"
#include <math.h>


int main(){
	char input[1024], output[1024];
	char charInput;
	int originBase = 0, targetBase = 0, inputIndex = 0;
	int check = 0;
	unsigned int decValue = 0;
	void isValidChar(char numInput, int originBase);
	unsigned int numToDecimal(char input[], int originBase, int inputIndex);
	void decimalToTargetBase(unsigned int decValue, int targetBase, char output[]);
	SP_BUFF_SET();

	/* start get origin base from user*/
	printf("Please enter the number's base:\n");
	check = scanf("%d",&originBase);
	if (check == 0) {
		printf("An error occurred!\n");
		exit(0);
	}
	if(!(originBase >= 2 && originBase<= 16)){
		printf("Invalid input base\n");
		exit(0);
	}
	/*end get origin base from user*/

	/* start get target base from user*/
	printf("Please enter the desired base:\n");
	check = scanf("%d",&targetBase);
	if (check == 0) {
		printf("An error occurred!\n");
		exit(0);
	}
	if(!(targetBase >= 2 && targetBase<= 16)){
		printf("Invalid desired base\n");
		exit(0);
	}
	/*end get target base from user*/

	/*get number for base change*/
	printf("Please enter a number in base %d:\n",originBase);
	charInput = getchar();
	charInput = getchar();

	while(charInput != EOF && charInput != '\n'){
		isValidChar(charInput, originBase);
		input[inputIndex] = charInput;
		inputIndex++;
		charInput = getchar();
	}
	--inputIndex;

	if(originBase != targetBase){
		decValue = numToDecimal(input, originBase, inputIndex);
		if(targetBase != 10){
			decimalToTargetBase(decValue, targetBase, output);
		}else{
			printf("The result is: %d\n", decValue);
			exit(1);
		}
	}
	printf("The result is: %s\n", input);

	return 0;
}

/*checks if the char of num is from the right base*/
void isValidChar(char numInput, int originBase){
	int numInputVal;
	/*first checks for bases below 10*/
	if(originBase < 10){
		numInputVal = numInput - '0';
		 if((numInputVal >= originBase) && (numInputVal >= 0)){
			 printf("Invalid number!\n");
			 exit(0);
		 }
	}else{ /* checks for bases above 10*/
		if((65 <= numInput) && (numInput <= 70)){	/*checks for letter input in bases above 10*/
			numInputVal = numInput - '7';
		}else if((97 <= numInput) && (numInput <= 102)){	/*checks for num input in bases above 10*/
			numInputVal = numInput - 'W';
		}else{
			numInputVal = numInput - '0';
		}
		if((numInputVal >= originBase) && (numInputVal < 0)){
			 printf("Invalid number!\n");
			 exit(0);
		}
	}
}

unsigned int calcPow(int base, int exp){
	int i;
	unsigned int power = 1;
	for (i = 1; i <= exp; i++) {
		power *= base;
	}
	return power;
}

unsigned int numToDecimal(char input[], int originBase, int inputIndex){
	unsigned int maxPower;
	unsigned int decValue = 0;
	int i;
	maxPower = calcPow(originBase, inputIndex);
	for(i = 0; i <= inputIndex; i++){
		if((input[i] >= 65) && (input[i] <= 70)){
			decValue += ((input[i] - '7') * maxPower);
			maxPower /= originBase;
		}else if((input[i] >= 48) && (input[i] <= 57)){
			decValue += ((input[i] - '0') * maxPower);
			maxPower /= originBase;
		}else{
			decValue += ((input[i] - 'W') * maxPower);
			maxPower /= originBase;
		}
	}
	return decValue;
}


void decimalToTargetBase(unsigned int decValue, int targetBase, char output[]){
	char numRep[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	char reversedOutput[1024];
	int remainder = 0;
	int revOutputIndex = 0, outputIndex, reverseOutputSize = 0;
	while(decValue > 0){
		remainder = decValue % targetBase;
		reversedOutput[revOutputIndex] = numRep[remainder];
		decValue /= targetBase;
		revOutputIndex++;
	}

	reverseOutputSize = revOutputIndex;
	revOutputIndex = reverseOutputSize - 1;

	for(outputIndex = 0; outputIndex < reverseOutputSize  ; outputIndex++){
		output[outputIndex] = reversedOutput[revOutputIndex];
		revOutputIndex--;
	}

	output[outputIndex++] = '\0';
	printf("The result is: %s\n",output);
	exit(1);
}
