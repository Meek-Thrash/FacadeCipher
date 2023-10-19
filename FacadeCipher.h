/*

This is a facade for a simpler use of the AES256 class from the Arduino Cryptography Library 
developed by Rhys Weatherley: https://rweather.github.io/arduinolibs/crypto.html;
Instead of encrypting and decrypting every block manually this class encrypts and decrypts the whole
plaintext/encrypted message;
in addition this facade class provides functions to encrypt and decrypt String messages;

see the README.txt file for the documentation

*/

#pragma once

#include <AES.h>
#include <BlockCipher.h>
#include <Crypto.h>


#define DEFAULT_PWD_LENGTH      				32
#define DEFAULT_MAX_RANDOM_VAL					1000
#define DEFAULT_PADDING_VALUE					0
#define MAX_UINT8_T_VAL						256


#ifndef FacadeCipher_H
#define FacadeCipher_H

 
class FacadeCipher
{
	public:

		int blockSize;
		bool keyOk;
		
		
		FacadeCipher(uint8_t* key, int keyLen)
		{
			
			uint8_t cleanedKey[DEFAULT_PWD_LENGTH] = {};
			
			for(int i = 0; i < DEFAULT_PWD_LENGTH; i++)
			{
				if(i < keyLen)
					cleanedKey[i] = key[i];
				else
					cleanedKey[i] = int(random(DEFAULT_MAX_RANDOM_VAL) % MAX_UINT8_T_VAL);
			}
			
			this->cipher =  new AES256();
			keyOk = cipher->setKey(cleanedKey, DEFAULT_PWD_LENGTH);
			blockSize = cipher->blockSize();
		};


		FacadeCipher(String key)
		{
			
			uint8_t cleanedKey[DEFAULT_PWD_LENGTH] = {};
			
			for(int i = 0; i < DEFAULT_PWD_LENGTH; i++)
			{
				if(i < key.length())
					cleanedKey[i] = key.charAt(i);
				else
					cleanedKey[i] = int(random(DEFAULT_MAX_RANDOM_VAL) % MAX_UINT8_T_VAL);
			}
			
			this->cipher =  new AES256();
			keyOk = cipher->setKey(cleanedKey, DEFAULT_PWD_LENGTH);
			blockSize = cipher->blockSize();
		};
		
		
		~FacadeCipher()
		{
			cipher->clear();
		};


		void FacadeCipher :: encrypt (uint8_t* msgIn, int msgLen, uint8_t* encryptedOut, int encLen)
		{
			uint8_t plainTxt[encLen] = {};
			
			for(int i = 0; i < encLen; i++)
			{
				if(i >= msgLen)
					plainTxt[i] = DEFAULT_PADDING_VALUE;
				else
					plainTxt[i] = msgIn[i];
			}
			
			
			int blocks = encLen / blockSize;

			uint8_t inBuff[blockSize];
			uint8_t outBuff[blockSize];
			
			for(int i = 0; i < blocks; i++)
			{
				for(int j = 0; j < blockSize; j++)
					inBuff[j] = plainTxt[(i * blockSize) + j];

				cipher->encryptBlock(outBuff, inBuff);

				for(int j = 0; j < blockSize; j++)
					encryptedOut[(i * blockSize) + j] = outBuff[j];
			}
		};
		
		
		void FacadeCipher :: decrypt (uint8_t* encryptedIn, int encLen, uint8_t* plainTxtOut)
		{
			int blocks = encLen / blockSize;

			uint8_t plainTxt[encLen];
			uint8_t inBuff[blockSize];
			uint8_t outBuff[blockSize];
			
			for(int i = 0; i < blocks; i++)
			{
				for(int j = 0; j < blockSize; j++)
					inBuff[j] = encryptedIn[(i * blockSize) + j];

				cipher->decryptBlock(outBuff, inBuff);

				for(int j = 0; j < blockSize; j++)
					plainTxtOut[(i * blockSize) + j] = outBuff[j];
			}
		};
		
		
		String FacadeCipher :: encryptString (String msgIn)
		{
			int msgLen = msgIn.length();
			int missingChars = blockSize - (msgLen % blockSize);
			int plainTxtSize = msgLen + missingChars;
			String encryptedOut = "";
			
			uint8_t plainTxt[plainTxtSize] = {};
			
			for(int i = 0; i < plainTxtSize; i++)
				if(i >= msgLen)
					plainTxt[i] = DEFAULT_PADDING_VALUE;
				else
					plainTxt[i] = (uint8_t)(msgIn.charAt(i));
			
			int blocks = plainTxtSize / blockSize;

			uint8_t inBuff[blockSize];
			uint8_t outBuff[blockSize];
			
			for(int i = 0; i < blocks; i++)
			{
				for(int j = 0; j < blockSize; j++)
					inBuff[j] = plainTxt[(i * blockSize) + j];

				cipher->encryptBlock(outBuff, inBuff);

				for(int j = 0; j < blockSize; j++)
					encryptedOut += char(outBuff[j]);
			}
			
			return encryptedOut;	
		};


		String FacadeCipher :: decryptString (String encryptedIn)
		{
			int encLen = encryptedIn.length();
			String plainTxtOut = "";
			
			uint8_t encryptedMsg[encLen] = {};
			
			for(int i = 0; i < encLen; i++)
				encryptedMsg[i] = (uint8_t)(encryptedIn.charAt(i));
			
			int blocks = encLen / blockSize;

			uint8_t inBuff[blockSize];
			uint8_t outBuff[blockSize];
			
			for(int i = 0; i < blocks; i++)
			{
				for(int j = 0; j < blockSize; j++)
					inBuff[j] = encryptedMsg[(i * blockSize) + j];

				cipher->decryptBlock(outBuff, inBuff);

				for(int j = 0; j < blockSize; j++)
					plainTxtOut += char(outBuff[j]);
			}

			return plainTxtOut;	
		};


	private:
		AES256* cipher;
};

#endif
