using System;
using NUnit.Framework;

namespace Measurement.UnitTests
{
    [TestFixture]
    public class MeasurementTests
    {
        [Test]
        public void DummyContourLines_Test1()
        {
            // Arrange - 1st phase of a Unit Test. Get the thing you need
            var x = new Measurement();

            const int testImage = 190087;
            string[] testLines =
            {
                "   Hello  ",
                "   World",
                "Seeya          "
            };
            
            // Act - 2nd. Do some stuff
            x.DummyContourLines(testImage, testLines);
            
            // Assert - 3rd. Check if the stuff are done write (or print them)
            x.DummyPrintContourLines();
            Assert.True(true);
            Console.WriteLine("DummyContourLines_Test1 exiting (salute).");
        }
    }
}
