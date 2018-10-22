using System;
using System.Collections;
using System.Collections.Generic;
using NUnit.Framework;

namespace Measurement.UnitTests
{
    [TestFixture]
    public class MeasurementTests
    {
        [Test]
        public void Measurement_BasicLoading()
        {
            // Arrange - 1st phase of a Unit Test. Get the thing you need
            const string filename = "path/to/your/image.tif"; // change this to a valid path
            var m = new Measurement(filename);

            // Act - 2nd. Do some stuff
            const string anotherFilename = "path/to/another/image.tif";
            const double scaling = 0.5;
            m.Load(anotherFilename, scaling);

            // Should properly display the image
            m.Display();

            // Access the image
            // Requires EMGU.CV in this Solution. Should we add another 200MB?
            // Emgu.CV.Structure.Mat loadedImage = m.Image;

            Console.WriteLine("Measurement_BasicLoading exiting (salute).");
        }

        [Test]
        public void FourCorners_Return8CoordinatesDoubleArray() // Function 1 in the PDF
        {
            // Arrange
            const string filename = "path/to/image";
            var m = new Measurement(filename);

            // Act
            // Should return the coordinates of four corners, clockwise
            /*
             * (AX, AY)-------------------------(BX, BY)
             * |                                       |
             * |                                       |
             * |                                       |
             * (DX, DY)-------------------------(CX, CY)
             * 
             */
            var corners = new double[8];
            var status = "";
            m.FourCorners(ref corners, ref status);

            // Assert
            Assert.That(corners[0] /* AX */ < corners[2] /* BX */);
            Assert.That(corners[0] /* AX */ < corners[6] /* DX */);
            Assert.That(corners[2] /* BX */ < corners[4] /* CX */);
            Assert.That(corners[6] /* DX */ < corners[4] /* CX */);
            Assert.That(corners[1] /* AY */ < corners[3] /* BY */);
            Assert.That(corners[1] /* AY */ < corners[7] /* DY */);
            Assert.That(corners[3] /* BY */ < corners[5] /* CY */);
            Assert.That(corners[7] /* DY */ < corners[5] /* CY */);
            Console.WriteLine(status);
        }

        [Test]
        public void RectangleData_IsRectangle_ReturnHeightWidthDiagonal_ReturnTrueIfRectangle() // Function 2 in PDF
        {
            const string rectFilename = "path/to/rectangle/part";
            const string notRectFilename = "path/to/not-rectangle/part";
            var m1 = new Measurement(rectFilename);
            var m2 = new Measurement(notRectFilename);

            Assert.IsTrue(m1.IsRectangle());
            Assert.IsFalse(m2.IsRectangle());

            var data = new double[3];
            var status = "";
            m1.RectangleData(ref data, ref status);
            Console.WriteLine("height = {0}, width = {1}, diagonal = {2}", data[0], data[1], data[2]);
            Console.WriteLine(status);

            m2.RectangleData(ref data, ref status);
            // Proper warning should be given when it is not a rectangle
            Console.WriteLine(status);
        }

        [Test]
        public void HoleData_ReturnListOfDouble3XYR() // Function 3 in PDF
        {
            const string filename = "path/to/image";
            var m = new Measurement(filename);
            
            List<double[]> data = new List<double[]>();
            string status = "";

            m.HoleData(ref data, ref status);
            
            for (int i = 0; i < data.Count; i++)
            {
                Console.WriteLine("Hole #{0}: X={1}, Y={2}, R={3}", i, data[0], data[1], data[2]);
                Console.WriteLine(status);
            }
        }
    }
}
