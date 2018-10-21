using System;
using System.Collections;

namespace Measurement
{
    public class Measurement
    {
        private readonly ArrayList _dummyContourLines; // dummy private member with setter and getter

        public Measurement() // constructor
        {
            _dummyContourLines = new ArrayList();
        }
        
        public void DummyContourLines(int dummyImage, string[] dummyLines) // dummy method
        {
            
            foreach (var line in dummyLines)
            {
                _dummyContourLines.Add(line.Trim());
            }

            Console.WriteLine("Here is DummyContourLines, " + dummyImage);
        }

        public void DummyPrintContourLines()
        {
            foreach (var line in _dummyContourLines)
            {
                Console.WriteLine(line);
            }
        }
    }
}
