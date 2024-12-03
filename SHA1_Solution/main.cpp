#include<stdio.h>
#include<malloc.h>
#include<openssl/sha.h>
#include <exception>


int main() {

	FILE* fileToHash;

	fopen_s(&fileToHash, "four-byte-burger.png", "rb");
	if (fileToHash != NULL) {
		char* input;

		fseek(fileToHash, 0, SEEK_END);
		unsigned int fileLength = ftell(fileToHash);
		fseek(fileToHash, 0, SEEK_SET);

		input = (char*)malloc(fileLength);
		fread(input, fileLength, 1, fileToHash);

		SHA_CTX ctx;
		SHA1_Init(&ctx);

		unsigned int totalBlockOfBytes = (fileLength / SHA_DIGEST_LENGTH) * SHA_DIGEST_LENGTH;
		for (int i = 0; i < totalBlockOfBytes; i += SHA_DIGEST_LENGTH) {
			SHA1_Update(&ctx, &(input[i]), SHA_DIGEST_LENGTH);
		}

		unsigned int remainingBytes = fileLength % SHA_DIGEST_LENGTH;

		if (remainingBytes > 0) {
			SHA1_Update(&ctx, &(input[totalBlockOfBytes]), remainingBytes);
		}

		unsigned char result[SHA_DIGEST_LENGTH];
		SHA1_Final(result, &ctx);

		printf("\n\n SHA1 hash: ");
		for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
			printf_s("%02X ", result[i]);
		}
		printf_s("\n\n");

		free(input);
		fclose(fileToHash);
	}
	else {
		printf_s("The file request was not found in the same directory as the program.");
	}
	


	


	return 0;
}