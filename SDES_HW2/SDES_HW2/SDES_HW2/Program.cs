using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SDES_HW2
{
    class Program
    {
        static void Main(string[] args)
        {
            // Restructure main menu

            byte[] x = { 1, 0, 1, 1, 1, 1, 0, 1 }; // use for plain text
            string s = "00000010";
            byte[] y = StringToByte(s);

            PrintByte(x);
            PrintByte(y);


            string key = "1010000010";
            int[] keyArr = StringToKeyArr(key);

            //if keyArr elements returned contains all zeros
            // prompt user to re-enter 10-bit binary key
            // call StringToKeyArr() again

            PrintIntArray(keyArr);

            //Generate SDES key
            int[] combinedSubkeys = new int[(sizeof(long))*2];
            combinedSubkeys = GenerateSDESKey(keyArr); // 

            // Divide combinedSubkeys.Length into half
            // each subkey is sizeof(long) 8 bits long
            int[] firstSubkey = new int[8];
            int[] secondSubkey = new int[8];
            for (int i = 0; i < (combinedSubkeys.Length / 2); i++)
            {
                firstSubkey[i] = combinedSubkeys[i];
                secondSubkey[i] = combinedSubkeys[8 + i];
            }
            // Do something with subkeys, or pass both arrays as encryption params <-- used in FK function

            // To Encrypt
            byte[] cipherText = EncryptionSDES(x);
            PrintByte(cipherText);



            Console.ReadLine();
        }

        public static byte[] EncryptionSDES(byte[] plainText)
        {
            // Step 1: IP() Initial Permutation (Put in a separate function)
            //      [k0][k1][k2][k3][k4][k5][k6][k7]
            //      [ 1][ 0][ 1][ 1][ 1][ 1][ 0][ 1]
            // IP:  [k1][k5][k2][k0][k3][k7][k4][k6]
            //      [ 0][ 1][ 1][ 1][ 1][ 1][ 1][ 0]
            byte[] newPlainArr = new byte[] { 0, 0, 0, 0, 0, 0, 0, 0 };
            newPlainArr[0] = plainText[1];
            newPlainArr[1] = plainText[5];
            newPlainArr[2] = plainText[2];
            newPlainArr[3] = plainText[0];
            newPlainArr[4] = plainText[3];
            newPlainArr[5] = plainText[7];
            newPlainArr[6] = plainText[4];
            newPlainArr[7] = plainText[6];


            int[] leftHalf = new int[] { 0, 0, 0, 0 };
            int[] rightHalf = new int[] { 0, 0, 0, 0 }; // <-- Fk Right
            for (int i = 0; i < (newPlainArr.Length / 2); i++)
            {
                leftHalf[i] = newPlainArr[i];
                rightHalf[i] = newPlainArr[4 + i];
            }

            // Step 2: Complex function FK()
            // Permutation + Substitution
            // --depends on a key input
            // (put in a separate function)
            // Input: 8-bit new newPlainArr[] or
            // leftHalf[],           rightHalf[]
            // [ 0][ 1][ 1][ 1]     [ 1][ 1][ 1][ 0]
            // Ouput: P4() = [f1][f3][f2][f0] <---Fk Left

            // byte[] leftHalf = FK(leftHalf); // function call to fk
            

            // Step 3: SW() Simple Permutation Function (put in a separate function)
            // --switches the two halves of the data
            // swap leftHalf and rightHalf
            // [0][1][1][1]     [1][1][1][0]
            // [1][1][1][0]     [0][1][1][1]
            for(int i = 0; i < leftHalf.Length; i++)
            {
                int temp = leftHalf[i]; 
                leftHalf[i] = rightHalf[i];
                rightHalf[i] = temp;
            }

            // Step 4: Complex function FK()
            // Input: 8-bit new newPlainArr[] or
            // leftHalf[],       rightHalf[]
            // [1][1][1][0]      [0][1][1][1]
            // Ouput: P4() = [f1][f3][f2][f0] <---Fk Left
           
            // byte[] leftHalf = FK(leftHalf); // function call to fk
            // rightHalf is still [0][1][1][1]
            // newPlainArr = leftHalf[] + rightHalf[];
            for (int i = 0; i < (newPlainArr.Length/2); i++)
            {
                newPlainArr[i] = (byte)leftHalf[i];
                newPlainArr[4 + i] = (byte)rightHalf[i];
            }
            
            // Step 5: IPInverse() -- Final Permutation Function
            // ex:   [k0][k1][k2][k3][k4][k5][k6][k7]
            //       [ 1][ 1][ 1][ 0][ 0][ 1][ 1][ 1]
            // IP-1: [k3][k0][k2][k4][k6][k1][k7][k5]
            //       [ 0][ 1][ 1][ 0][ 1][ 1][ 1][ 1]
            byte[] cipherArr = new byte[] { 0, 0, 0, 0, 0, 0, 0, 0 };
            cipherArr[0] = newPlainArr[3];
            cipherArr[1] = newPlainArr[0];
            cipherArr[2] = newPlainArr[2];
            cipherArr[3] = newPlainArr[4];
            cipherArr[4] = newPlainArr[6];
            cipherArr[5] = newPlainArr[1];
            cipherArr[6] = newPlainArr[7];
            cipherArr[7] = newPlainArr[5];

            return cipherArr;
        }

        public static int[] GenerateSDESKey(int[] keyArr)
        {

            // keyArr[] : 10-bit key
            //      [ 1][ 0][ 1][ 0][ 0][ 0][ 0][ 0][ 1][ 0]
            //      [k0][k1][k2][k3][k4][k5][k6][k7][k8][k9]
            // P10: [k2][k4][k1][k6][k3][k9][k0][k8][k7][k5]


            // Step 1: Permute P10
            //      [k0][k1][k2][k3][k4][k5][k6][k7][k8][k9]
            // P10: [k2][k4][k1][k6][k3][k9][k0][k8][k7][k5]
            //      [ 1][ 0][ 0][ 0][ 0][ 0][ 1][ 1][ 0][ 0]
            int[] newKeyArr = new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            newKeyArr[0] = keyArr[2];
            newKeyArr[1] = keyArr[4];
            newKeyArr[2] = keyArr[1];
            newKeyArr[3] = keyArr[6];
            newKeyArr[4] = keyArr[3];
            newKeyArr[5] = keyArr[9];
            newKeyArr[6] = keyArr[0];
            newKeyArr[7] = keyArr[8];
            newKeyArr[8] = keyArr[7];
            newKeyArr[9] = keyArr[5];


            //PrintIntArray(newKeyArr);

            // Step 2: Circular left shift LS-1
            //      [ 1][ 0][ 0][ 0][ 0]    [ 0][ 1][ 1][ 0][ 0]
            //      [k0][k1][k2][k3][k4]    [k5][k6][k7][k8][k9]
            //      [ 0][ 0][ 0][ 0][ 1]    [ 1][ 1][ 0][ 0][ 0]
            int shift = 1;
            int[] firstHalf = new int[] { 0, 0, 0, 0, 0 };
            int[] secondHalf = new int[] { 0, 0, 0, 0, 0 };
            for (int i = 0; i < (newKeyArr.Length/2); i++)
            {
                firstHalf[i] = newKeyArr[i];
                secondHalf[i] = newKeyArr[5 + i];
            }

            for (int i = 0; i < (newKeyArr.Length / 2); i++)
            {
                newKeyArr[i] = firstHalf[(i + shift + 5) % 5];
                newKeyArr[5 + i] = secondHalf[(i + shift + 5) % 5];
            }

            // Step 3: Permute P8
            //      [ 0][ 0][ 0][ 0][ 1][ 1][ 1][ 0][ 0][ 0]
            //      [k0][k1][k2][k3][k4][k5][k6][k7][k8][k9]
            // Subkey 1 (Global Var)?
            //      [k5][k2][k6][k3][k7][k4][k9][k8]
            //      [ 1][ 0][ 1][ 0][ 0][ 1][ 0][ 0]
            int[] firstSubkey = new int[] { 0, 0, 0, 0, 0, 0, 0, 0 };
            firstSubkey[0] = newKeyArr[5];
            firstSubkey[1] = newKeyArr[2];
            firstSubkey[2] = newKeyArr[6];
            firstSubkey[3] = newKeyArr[3];
            firstSubkey[4] = newKeyArr[7];
            firstSubkey[5] = newKeyArr[4];
            firstSubkey[6] = newKeyArr[9];
            firstSubkey[7] = newKeyArr[8];

            // Step 4: Circular left shift LS-2
            //      [ 0][ 0][ 0][ 0][ 1]    [ 1][ 1][ 0][ 0][ 0]
            //      [k0][k1][k2][k3][k4]    [k5][k6][k7][k8][k9]
            //      [ 0][ 0][ 1][ 0][ 0]    [ 0][ 0][ 0][ 1][ 1]
            shift = 2;
            for (int i = 0; i < (newKeyArr.Length / 2); i++)
            {
                firstHalf[i] = newKeyArr[i];
                secondHalf[i] = newKeyArr[5 + i];
            }
            for (int i = 0; i < (newKeyArr.Length / 2); i++)
            {
                newKeyArr[i] = firstHalf[(i + shift + 5) % 5];
                newKeyArr[5 + i] = secondHalf[(i + shift + 5) % 5];
            }

            // Step 5: Permute P8
            //      [ 0][ 0][ 1][ 0][ 0][ 0][ 0][ 0][ 1][ 1]
            //      [k0][k1][k2][k3][k4][k5][k6][k7][k8][k9]
            // Subkey 2 (Global Var)
            //      [k5][k2][k6][k3][k7][k4][k9][k8]
            //      [ 0][ 1][ 0][ 0][ 0][ 0][ 1][ 1]
            int[] secondSubkey = new int[] { 0, 0, 0, 0, 0, 0, 0, 0 };
            secondSubkey[0] = newKeyArr[5];
            secondSubkey[1] = newKeyArr[2];
            secondSubkey[2] = newKeyArr[6];
            secondSubkey[3] = newKeyArr[3];
            secondSubkey[4] = newKeyArr[7];
            secondSubkey[5] = newKeyArr[4];
            secondSubkey[6] = newKeyArr[9];
            secondSubkey[7] = newKeyArr[8];

            // combine 8-bit firstSubkey[] + 8-bit secondSubkey[] = 16-bit int[] combined subkeys
            int[] combinedSubkeys = new int[firstSubkey.Length + secondSubkey.Length];
            for (int i = 0; i < (combinedSubkeys.Length / 2); i++)
            {
                combinedSubkeys[i] = (byte)firstSubkey[i];
                combinedSubkeys[firstSubkey.Length + i] = (byte)secondSubkey[i];
            }
            // return int[] combinedSubkeys (divide combinedSubkeys.Length / 2 in the caller)
            return combinedSubkeys;
        }

                                                                        //Byte & String Manipulation functions
        //ByteToString - converts byteArray to string
        public static string ByteToString(byte[] byteArray)
        {
            if (ValidateByteArray(byteArray))
            {
                return System.Text.Encoding.UTF8.GetString(byteArray);
            }
            else
            {
                Console.WriteLine("Invalid bytearray in ByteToString");
                return "NULLSTR";
            }
        }

        //StringToByte - converts byte array, 8 bits long, to a string
        public static byte[] StringToByte(string str)
        {
            byte[] byteArray = new byte[] { 0, 0, 0, 0, 0, 0, 0, 0 };
            

            for (int i=0; i < str.Length; ++i)
            {
                if (!str[i].Equals('0') && !str[i].Equals('1'))
                {
                    Console.WriteLine("non 0-1 char passed into str, Error, returning empty ByteArray");
                    return null;
                }
                else
                {
                    if (str[i] == '1')
                    {
                        byteArray[i] = 1;
                    }
                    else
                    {
                        byteArray[i] = 0;
                    }
                }
            }

            return byteArray;
        }

        //StringToKeyArr - converts string key to int array, 10 bits long
        public static int[] StringToKeyArr(string key)
        {
            int[] keyArr = new int[] { 0, 0, 0, 0, 0, 0, 0, 0 , 0, 0 };

            if (key.Length == 10)
            {
                for (int i = 0; i < key.Length; ++i)
                {
                    if (!key[i].Equals('0') && !key[i].Equals('1'))
                    {
                        Console.WriteLine("non 0-1 char passed into str, Error, returning empty Array");
                        return null;
                    }
                    else
                    {
                        if (key[i] == '1')
                        {
                            keyArr[i] = 1;
                        }
                        else
                        {
                            keyArr[i] = 0;
                        }
                    }
                }
            }
            else
            {
                Console.WriteLine("Key must be 10 bits long. Returning key of [0000000000]!\n");
            }

            return keyArr;
        }

        //prints a ByteArray out that is either 8 or 10-bits long
        public static void PrintByte(byte[] byteArray)
        {
            if (byteArray.Length == 8)
            {
                if (ValidateByteArray(byteArray) == true)
                {
                    Console.Write("{0}{1}{2}{3}{4}{5}{6}{7}\n", byteArray[0], byteArray[1], byteArray[2], byteArray[3], byteArray[4], byteArray[5], byteArray[6], byteArray[7]);
                }
                else
                {
                    Console.Write("There was an error in validating byte array ");
                    Console.Write("{0}{1}{2}{3}{4}{5}{6}{7}\n", byteArray[0], byteArray[1], byteArray[2], byteArray[3], byteArray[4], byteArray[5], byteArray[6], byteArray[7]);
                }
            }
            else if (byteArray.Length == 10)
            {
                if (ValidateByteArray(byteArray) == true)
                {
                    Console.Write("{0}{1}{2}{3}{4}{5}{6}{7}{8}{9}\n", byteArray[0], byteArray[1], byteArray[2], byteArray[3], byteArray[4], byteArray[5], byteArray[6], byteArray[7], byteArray[8], byteArray[9]);
                }
                else
                {
                    Console.Write("There was an error in validating byte array ");
                    Console.Write("{0}{1}{2}{3}{4}{5}{6}{7}{8}{9}\n", byteArray[0], byteArray[1], byteArray[2], byteArray[3], byteArray[4], byteArray[5], byteArray[6], byteArray[7], byteArray[8], byteArray[9]);
                }
            }
            else
            {
                Console.WriteLine("Invalid Byte Length, must be 8 or 10 bit long");
            }
        }

        //Prints an Int array of 10-elements/bits (for key)
        public static void PrintIntArray(int[] intArr)
        {
            if (intArr.Length == 10)
            {
                if (CheckBinaryArr(intArr) == true)
                {
                    Console.Write("{0}{1}{2}{3}{4}{5}{6}{7}{8}{9}\n", intArr[0], intArr[1], intArr[2], intArr[3], intArr[4], intArr[5], intArr[6], intArr[7], intArr[8], intArr[9]);
                }
                else
                {
                    Console.Write("There was an error in validating byte array ");
                    Console.Write("{0}{1}{2}{3}{4}{5}{6}{7}{8}{9}\n", intArr[0], intArr[1], intArr[2], intArr[3], intArr[4], intArr[5], intArr[6], intArr[7], intArr[8], intArr[9]);
                }
            }
            //else
            //{
            //    Console.WriteLine("Invalid Byte Length, must be 10 bit long");
            //}
        }

        //Checks if the Int array contains only 0's and 1's
        public static bool CheckBinaryArr(int[] array)
        {
            for (int i = 0; i < array.Length; ++i)
            {
                if (array[i] != 1 && array[i] != 0)
                {
                    return false;
                }
            }
            return true;
        }

        //confirms that a byteArray contains only 0's and 1's
        public static bool ValidateByteArray(byte[] byteArray)
        {
            for (int i = 0; i < byteArray.Length; ++i)
            {
                if (byteArray[i] != 1 && byteArray[i] != 0)
                {
                    return false;
                }
            }
            return true;
        }
    }
}
