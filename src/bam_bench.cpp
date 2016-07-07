//#define SEQAN_ALIGN_SIMD_PROFILE 1
//#define SEQAN_ENABLE_TESTING 0
//#define SEQAN_ENABLE_DEBUG 0

#include <iostream>
#include <seqan/basic.h>
#include <seqan/arg_parse.h>
#include <seqan/stream.h>
//#include <seqan/align.h>
#include <seqan/bam_io.h>
#include <random>

using namespace seqan;


int main(int argc, char* argv[])
{
    BamFileIn bamFile;
    if (!open(bamFile, argv[1]))
    {
        std::cerr << "Could not open: " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    BamHeader bamHeader;
    readHeader(bamHeader, bamFile);

    using TPosition = typename Position<BamFileIn>::Type;
    seqan::String<seqan::Pair<TPosition, int> > recs;

    seqan::BamAlignmentRecord record;
    while (!atEnd(bamFile))
    {
        TPosition ofs = position(bamFile);
        readRecord(record, bamFile);
        appendValue(recs, seqan::Pair<TPosition, int>(ofs, record.beginPos));
    }

    for (size_t j = 0; j < length(recs); ++j)
    {
        setPosition(bamFile, recs[j].i1);
        readRecord(record, bamFile);
//        SEQAN_ASSERT_EQ(record.beginPos, recs[j].i2);
    }

    std::mt19937 rng(/*seed=*/1);
    std::uniform_int_distribution<long> pdf(0, length(recs) - 1);

    for (size_t i = 0; i < 100000; ++i)
    {
        long j = pdf(rng);
        setPosition(bamFile, recs[j].i1);
        readRecord(record, bamFile);
//        SEQAN_ASSERT_EQ(record.beginPos, recs[j].i2);
    }

    return EXIT_SUCCESS;
}