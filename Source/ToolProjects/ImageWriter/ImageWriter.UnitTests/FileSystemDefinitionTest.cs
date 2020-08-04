using Microsoft.VisualStudio.TestTools.UnitTesting;
using FluentAssertions;

namespace ImageWriter.UnitTests
{
    [TestClass]
    public class FileSystemDefinitionTest
    {
        public TestContext TestContext { get; set; }
        public FileSystemDefinition Context1 { get; set; }
        public FileSystemDefinition Context2 { get; set; }

        [TestInitialize]
        public void MyTestInitialize()
        {
            // File System Layout
            // 
            // Name             Size (bytes)    Size (sectors)  Offset (bytes)  Offset (sectors)
            // Boot Sector      512             1               0               0
            // FSD              512             1               512             1
            // CAT              3160            7               1024            2
            // DA               3235840         6320            4608            9
            // 
            // Boot Sector      2048            1               0               0
            // FSD              2048            1               2048            1
            // CAT              3160            2               4096            2
            // DA               12943360        6320            8192            4

            Context1 = new FileSystemDefinition
            {
                SectorSizeInBytes = 512,
                ClusterSizeInSectors = 8,
                NumberOfCatEntries = 790
            };

            Context2 = new FileSystemDefinition
            {
                SectorSizeInBytes = 2048,
                ClusterSizeInSectors = 8,
                NumberOfCatEntries = 790
            };
        }

        [TestMethod]
        public void TestClusterSizeInBytesGetAssessor()
        {
            Context1.ClusterSizeInBytes.Should().Be(4096);
            Context2.ClusterSizeInBytes.Should().Be(16384);
        }

        [TestMethod]
        public void TestSectorCountGetAssessor()
        {
            Context1.SectorCount.Should().Be(6329);
            Context2.SectorCount.Should().Be(6324);
        }

        [TestMethod]
        public void TestClusterCountGetAssessor()
        {
            Context1.ClusterCount.Should().Be(790);
            Context2.ClusterCount.Should().Be(790);
        }

        [TestMethod]
        public void TestCatSizeInExactBytesGetAssessor()
        {
            Context1.CatSizeInExactBytes.Should().Be(3160);
            Context2.CatSizeInExactBytes.Should().Be(3160);
        }

        [TestMethod]
        public void TestCatSizeInBytesGetAssessor()
        {
            Context1.CatSizeInBytes.Should().Be(3584);
            Context2.CatSizeInBytes.Should().Be(4096);
        }

        [TestMethod]
        public void TestCatSizeInSectorsGetAssessor()
        {
            Context1.CatSizeInSectors.Should().Be(7);
            Context2.CatSizeInSectors.Should().Be(2);
        }

        [TestMethod]
        public void TestDataAreaOffsetInBytesGetAssessor()
        {
            Context1.DataAreaOffsetInBytes.Should().Be(4608);
            Context2.DataAreaOffsetInBytes.Should().Be(8192);
        }

        [TestMethod]
        public void TestDataAreaOffsetInSectorsGetAssessor()
        {
            Context1.DataAreaOffsetInSectors.Should().Be(9);
            Context2.DataAreaOffsetInSectors.Should().Be(4);
        }

        [TestMethod]
        public void TestDataSizeInBytesGetAssessor()
        {
            Context1.DataAreaSizeInBytes.Should().Be(3235840);
            Context2.DataAreaSizeInBytes.Should().Be(12943360);
        }

        [TestMethod]
        public void TestDataSizeInSectorsGetAssessor()
        {
            Context1.DataAreaSizeInSectors.Should().Be(6320);
            Context2.DataAreaSizeInSectors.Should().Be(6320);
        }

        [TestMethod]
        public void TestGetBytes()
        {
            var result1 = Context1.GetBytes();
            var result2 = Context2.GetBytes();

            // The length of the array should be sector size.
            result1.Length.Should().Be(512);
            result2.Length.Should().Be(2048);
        }
    }
}