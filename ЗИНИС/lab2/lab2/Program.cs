using System;
using System.IO;
using System.Linq;

namespace lab2
{
    class Program
    {
        static void Main(string[] args)
        {
            double english = 0;
            double russian = 0;
            double binary = 0;
            string EngLetters = "ABCDEFGHIJKLMNOPQTRSTVWXYZ";
            Console.WriteLine("----------1a----------");
            int[] countLetter = new int[26];
            int countLettersInFile = 0;
            double[] probabilityLetters = new double[26];
            using (StreamReader streamReader = new StreamReader(@"D:\лабы\5-й сем\ЗИНИС\lab2\english.txt"))
            {
                string file = streamReader.ReadToEnd().ToUpper();
                countLettersInFile = file.Count();
                Console.WriteLine($"Количество символов в файле: {countLettersInFile}");
                Console.WriteLine();
                Console.WriteLine("Количество вхождений каждой буквы:");
                for (int j = 0; j < 26; j++)
                {
                    countLetter[j] = file.Count(x => x == EngLetters[j]);
                    Console.WriteLine($"{ EngLetters[j]}: { countLetter[j]}");
                    probabilityLetters[j] = (double)countLetter[j] / countLettersInFile;
                    Console.WriteLine($"P({EngLetters[j]}): {probabilityLetters[j]}");
                    Console.WriteLine();
                    if (countLetter[j] != 0)
                    {
                        english += probabilityLetters[j] * (Math.Log(probabilityLetters[j]) / Math.Log(2)) * (-1);
                    }
                }
                Console.WriteLine("Энтропия английского алфавита:");
                Console.WriteLine(english);
            }
            Console.WriteLine("----------------------------------------------------------");
            int[] countLetter2 = new int[33];
            int countLettersInFile2 = 0;
            double[] probabilityLetters2 = new double[33];

            string letters2 = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
            using (StreamReader streamReader = new StreamReader(@"D:\лабы\5-й сем\ЗИНИС\lab2\russian.txt"))
            {
                string file2 = streamReader.ReadToEnd().ToLower();
                countLettersInFile2 = file2.Count();
                Console.WriteLine($"Количество символов в файле: {countLettersInFile2}");
                Console.WriteLine();
                Console.WriteLine("Количество вхождений каждой буквы:");
                for (int j = 0; j < 33; j++)
                {
                    countLetter2[j] = file2.Count(x => x == letters2[j]);
                    Console.WriteLine($"{ letters2[j]}: { countLetter2[j]}");
                    probabilityLetters2[j] = (double)countLetter2[j] / countLettersInFile2;
                    Console.WriteLine($"P({letters2[j]}): {probabilityLetters2[j]}");
                    Console.WriteLine();
                    if (countLetter2[j] != 0)
                    {
                        russian += probabilityLetters2[j] * (Math.Log(probabilityLetters2[j]) / Math.Log(2)) * (-1);
                    }
                }
                Console.WriteLine("Энтропия русского алфавита:");
                Console.WriteLine(russian);
            }
            Console.WriteLine("----------1б----------");

            int[] countLetter3 = new int[2];
            int countLettersInFile3 = 0;
            double[] probabilityLetters3 = new double[2];

            string letters3 = "01";
            using (StreamReader streamReader = new StreamReader(@"D:\лабы\5-й сем\ЗИНИС\lab2\binary.txt"))
            {
                string file3 = streamReader.ReadToEnd();
                countLettersInFile3 = file3.Count();
                Console.WriteLine($"Количество символов в файле: {countLettersInFile3}");
                Console.WriteLine();
                Console.WriteLine("Количество вхождений каждой цифры:");

                for (int j = 0; j < 2; j++)
                {
                    countLetter3[j] = file3.Count(x => x == letters3[j]);
                    Console.WriteLine($"{ letters3[j]}: { countLetter3[j]}");

                    probabilityLetters3[j] = (double)countLetter3[j] / countLettersInFile3;
                    Console.WriteLine($"P({letters3[j]}): {probabilityLetters3[j]}");
                    Console.WriteLine();

                    binary += (probabilityLetters3[j] * (Math.Log(probabilityLetters3[j])) / Math.Log(2)) * (-1);

                }
                Console.WriteLine("Энтропия бинарного алфавита:");
                Console.WriteLine(binary);
            }
            Console.WriteLine();
            Console.WriteLine("----------1в----------");
            Console.WriteLine("Введите фио:");
            string fio= Console.ReadLine();
            double countRussianInformation = russian * fio.Replace(" ", "").ToLower().Count();
            double countBinaryInformation = binary * fio.Replace(" ", "").ToLower().Count();
            Console.WriteLine("Количество информации на основе энтропии русского алфавита:");
            Console.WriteLine(countRussianInformation);

            Console.WriteLine("Количество информации на основе энтропии бинарного алфавита:");
            Console.WriteLine(countBinaryInformation);
            double ASCII = fio.ToLower().Count()*8;
            Console.WriteLine("Количество информации с использованием ASCII для бинарного алфавита: ");
            double countASCIIBinaryInformation = ASCII * binary;
            Console.WriteLine(countASCIIBinaryInformation);
            Console.WriteLine();
            Console.WriteLine("Количество информации с использованием ASCII для русского алфавита: ");
            double countASCIIRussianInformation = ASCII * russian;
            Console.WriteLine(countASCIIRussianInformation);
            Console.WriteLine();


            Console.WriteLine("----------1г----------");
            Console.WriteLine("-------------BINARY-------------");

            double p = 0.1;
            double q = 1 - p;
            Console.WriteLine("Веростяность ошибочной передачи = 0.1");
            double conditionalEntropyBinary = -p * (Math.Log(p) / Math.Log(2)) - q * (Math.Log(q) / Math.Log(2));
            Console.WriteLine($"Условная энтропия = {conditionalEntropyBinary}");
            double effectiveEntropyBinary = binary - conditionalEntropyBinary;
            Console.WriteLine($"Эффективная энтропия = {effectiveEntropyBinary}");
            countBinaryInformation = effectiveEntropyBinary * fio.Replace(" ", "").ToLower().Count();
            Console.WriteLine("Количество эффективной информации с использованием энтропии бинарного алфавита:");
            Console.WriteLine(countBinaryInformation);
            Console.WriteLine();

            p = 0.5;
            q = 1 - p;
            Console.WriteLine("Веростяность ошибочной передачи = 0.5");
            conditionalEntropyBinary = -p * Math.Log(p,2) - q * Math.Log(q,2);
            Console.WriteLine($"Условная энтропия = {conditionalEntropyBinary}");
            effectiveEntropyBinary = binary - conditionalEntropyBinary;
            Console.WriteLine($"Эффективная энтропия = {effectiveEntropyBinary}");
            countBinaryInformation = effectiveEntropyBinary * fio.Replace(" ", "").ToLower().Count();
            Console.WriteLine("Количество эффективной информации с использованием энтропии бинарного алфавита:");
            Console.WriteLine(countBinaryInformation);
            Console.WriteLine();


            p = 1.0;
            q = 1 - p;
            Console.WriteLine("Веростяность ошибочной передачи = 1.0");
            conditionalEntropyBinary = -p * (Math.Log(p) / Math.Log(2)) - q * (Math.Log(q) / Math.Log(2));
            Console.WriteLine($"Условная энтропия = {conditionalEntropyBinary}");
            conditionalEntropyBinary = binary - conditionalEntropyBinary;
            Console.WriteLine($"Эффективная энтропия = {effectiveEntropyBinary}");
            Console.WriteLine("Информация будет полностью ошибочна!");
            countBinaryInformation = effectiveEntropyBinary * fio.Replace(" ", "").ToLower().Count();
            Console.WriteLine("Количество эффективной информации с использованием энтропии бинарного алфавита:");
            Console.WriteLine(countBinaryInformation);
            Console.WriteLine();



            Console.WriteLine("-------------RUSSIAN-------------");

            p = 0.1;
            q = 1 - p;
            Console.WriteLine("Веростяность ошибочной передачи = 0.1");
            double conditionalEntropyRussian = -p * (Math.Log(p) / Math.Log(2)) - q * (Math.Log(q) / Math.Log(2));
            Console.WriteLine($"Условная энтропия = {conditionalEntropyBinary}");
            double effectiveEntropyRussian = russian - conditionalEntropyRussian;
            Console.WriteLine($"Эффективная энтропия = {effectiveEntropyBinary}");
            countRussianInformation = effectiveEntropyRussian * fio.Replace(" ", "").ToLower().Count();
            Console.WriteLine("Количество эффективной информации с использованием энтропии русского алфавита:");
            Console.WriteLine(countRussianInformation);
            Console.WriteLine();

            p = 0.5;
            q = 1 - p;
            Console.WriteLine("Веростяность ошибочной передачи = 0.5");
            conditionalEntropyRussian = -p * (Math.Log(p) / Math.Log(2)) - (q * (Math.Log(q) / Math.Log(2)));
            Console.WriteLine($"Условная энтропия = {conditionalEntropyRussian}");
            effectiveEntropyRussian = russian - conditionalEntropyRussian;
            Console.WriteLine($"Эффективная энтропия = {effectiveEntropyRussian}");
            countRussianInformation = effectiveEntropyRussian * fio.Replace(" ", "").ToLower().Count();
            Console.WriteLine("Количество эффективной информации с использованием энтропии русского алфавита:");
            Console.WriteLine(countRussianInformation);
            Console.WriteLine();

            p = 1.0;
            q = 1 - p;
            Console.WriteLine("Веростяность ошибочной передачи = 1.0");
            conditionalEntropyRussian = -p * (Math.Log(p) / Math.Log(2)) - q * (Math.Log(q) / Math.Log(2));
            Console.WriteLine($"Условная энтропия = {conditionalEntropyRussian}");
            effectiveEntropyRussian = russian - conditionalEntropyRussian;
            Console.WriteLine($"Эффективная энтропия = {effectiveEntropyRussian}");
            Console.WriteLine("Информация будет полностью ошибочна!");
            countRussianInformation = effectiveEntropyRussian * fio.Replace(" ", "").ToLower().Count();
            Console.WriteLine("Количество эффективной информации с использованием энтропии русского алфавита:");
            Console.WriteLine(countRussianInformation);
            Console.WriteLine();
        }
    }
}
