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
            byte[] x = {1, 0, 0, 0 ,0,0,0,1};
            string s = "00000010";
            byte[] y = StringToByte(s);

            PrintByte(x);
            PrintByte(y);
            
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
