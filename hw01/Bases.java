/**
 * CS 2110 Spring 2021 HW1
 * Part 2 - Coding with bases
 *
 * @author Que Le
 *
 * Global rules for this file:
 * - You may not use more than 2 conditionals per method. Conditionals are
 *   if-statements, if-else statements, or ternary expressions. The else block
 *   associated with an if-statement does not count toward this sum.
 * - You may not use more than 2 looping constructs per method. Looping
 *   constructs include for loops, while loops and do-while loops.
 * - You may not use nested loops.
 * - You may not declare any file-level variables.
 * - You may not use switch statements.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any method from this or
 *   another file to implement any method. Recursive solutions are not
 *   permitted.
 * - The only Java API methods you are allowed to invoke are:
 *     String.length()
 *     String.charAt()
 * - You may not invoke the above methods from string literals.
 *     Example: "12345".length()
 * - When concatenating numbers with Strings, you may only do so if the number
 *   is a single digit.
 *
 * Method-specific rules for this file:
 * - You may not use multiplication, division or modulus in any method, EXCEPT
 *   decimalStringToInt (only multiplication)
 * - You may declare exactly one String variable each in intToOctalString and
 *   and hexStringToBinaryString.
 */
public class Bases
{
    /**
     * Convert a string containing ASCII characters (in binary) to an int.
     *
     * You do not need to handle negative numbers. The Strings we will pass in
     * will be valid binary numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: binaryStringToInt("111"); // => 7
     */
    public static int binaryStringToInt(String binary)
    {
        int answer = 0;
		for (int i = 0; i < binary.length(); i++) {
            answer = answer << 1;
            answer += (int) binary.charAt(i) - 48;
        }
		return answer;
    }

    /**
     * Convert a string containing ASCII characters (in decimal) to an int.
     *
     * You do not need to handle negative numbers. The Strings we will pass in
     * will be valid decimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: decimalStringToInt("46"); // => 46
     *
     * You may use multiplication in this method.
     */
    public static int decimalStringToInt(String decimal)
    {
        int answer = 0;
        for (int i = 0 ; i < decimal.length() ; i++) {
            answer *= 10;
			answer += (int) decimal.charAt(i) - 48;
        }
        return answer;
    }

    /**
     * Convert a string containing ASCII characters (in hex) to an int.
     *
     * You do not need to handle negative numbers. The Strings we will pass in
     * will be valid hex numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: hexStringToInt("2B"); // => 43
     */
    public static int hexStringToInt(String hex)
    {
        int track = 0;
        int answer = 0;
		for (int i = hex.length() - 1 ; i >= 0; i--) {
            int temp = (int)hex.charAt(i) - 48;
			int number = temp;
			if (temp > 9) {
				number -= 7;
			}
			answer += number << track;
			track += 4;
		}
		return answer;
    }

    /**
     * Convert a int into a String containing ASCII characters (in octal).
     *
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters
     * necessary to represent the number that was passed in.
     *
     * Example: intToOctalString(166); // => "246"
     *
     * You may declare one String variable in this method.
     */
    public static String intToOctalString(int octal)
    {
        String answer = "";
        int track = 0;
        if (octal == 0) {
			return "0";
        }
        while (octal >= 1) {
            track = octal - ((octal >> 3) << 3);
			answer = track + answer;
			octal = octal >> 3; 
		}
        return answer;
    }

    /**
     * Convert a String containing ASCII characters representing a number in
     * hex into a String containing ASCII characters that represent that same
     * value in binary.
     *
     * The output string should only contain numbers.
     * You do not need to handle negative numbers.
     * The length of all the hex strings passed in will be of size 8.
     * The binary string returned should contain 32 characters.
     *
     * Example: hexStringToBinaryString("06A1E4C0"); // => 00000110101000011110010011000000
     *
     * You may declare one String variable in this method.
     */
    public static String hexStringToBinaryString(String hex)
    {
        int track = 0;
        int dec = 0;
        String answer = "";
        int bit = 31;
		for (int i = hex.length() - 1; i >= 0; i--) {
            int temp = (int)hex.charAt(i) - 48;
			int number = temp;
			if (temp > 9) {
				number -= 7;
			}
			dec += number << track;
			track += 4;
		}
        while (bit >= 0) {
            int k = dec >> bit;
            if ((k & 1) == 0)
                answer += "0";
            else
                answer += "1";
            bit--;
        }
        return answer;
    }
}