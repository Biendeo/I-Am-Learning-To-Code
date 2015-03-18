char encryptChar (char, int);
char decryptChar (char, int);

char encryptChar (char currentChar, int encryptionLevel) {
	
	// If currentChar is a capital letter
	if ((currentChar > '@') && (currentChar < '[')) {
		if ((currentChar % 2) == 0) {
			currentChar = currentChar + encryptionLevel;
		}
		else {
			currentChar = currentChar - encryptionLevel;
		}
		while (currentChar <= '@') {
			currentChar = currentChar + 26;
		}
		while (currentChar >= '[') {
			currentChar = currentChar - 26;
		}
	}
	
	// If currentChar is a lower-case letter
	if ((currentChar > '`') && (currentChar < '{')) {
		if ((currentChar % 2) == 0) {
			currentChar = currentChar + encryptionLevel;
		}
		else {
			currentChar = currentChar - encryptionLevel;
		}
		while (currentChar <= '`') {
			currentChar = currentChar + 26;
		}
		while (currentChar >= '{') {
			currentChar = currentChar - 26;
		}
	}
		
	
	return currentChar;
}

char decryptChar (char currentChar, int encryptionLevel) {
	
	// If currentChar is a capital letter
	if ((currentChar > '@') && (currentChar < '[')) {
		if ((currentChar % 2) == 0) {
			currentChar = currentChar - encryptionLevel;
		}
		else {
			currentChar = currentChar + encryptionLevel;
		}
		while (currentChar <= '@') {
			currentChar = currentChar - 26;
		}
		while (currentChar >= '[') {
			currentChar = currentChar + 26;
		}
	}
	
	// If currentChar is a lower-case letter
	if ((currentChar > '`') && (currentChar < '{')) {
		if ((currentChar % 2) == 0) {
			currentChar = currentChar - encryptionLevel;
		}
		else {
			currentChar = currentChar + encryptionLevel;
		}
		while (currentChar <= '`') {
			currentChar = currentChar - 26;
		}
		while (currentChar >= '{') {
			currentChar = currentChar + 26;
		}
	}
		
	
	return currentChar;
}