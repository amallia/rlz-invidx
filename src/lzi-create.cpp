#define ELPP_THREAD_SAFE

#include "utils.hpp"
#include "collection.hpp"
#include "lz_utils.hpp"

#include "indexes.hpp"

#include "logging.hpp"
INITIALIZE_EASYLOGGINGPP

int main(int argc, const char* argv[])
{
    setup_logger(argc, argv);

    /* parse command line */
    LOG(INFO) << "Parsing command line arguments";
    auto args = utils::parse_args_lz(argc, argv);

    /* parse the collection */
    LOG(INFO) << "Parsing collection directory " << args.collection_dir;
    invidx_collection col(args.collection_dir);

    /* create rlz index */
    const uint32_t factorization_blocksize = 64 * 1024;
    /*
    {
        auto lz_store_docs = typename lz_store<coder::zlib<9>, factorization_blocksize>::builder{}
                            .set_rebuild(args.rebuild)
                            .set_threads(args.threads)
                            .build_or_load(col,col.docs_file,"D-ZLIB-9");
        verify_index(col.docs_file, lz_store_docs);
        
        auto docs_bytes = lz_store_docs.size_in_bytes();
        auto docs_bits = docs_bytes * 8;
        LOG(INFO) << "D-ZLIB-9 bytes = " << docs_bytes;
        double DBPI = docs_bits / double(col.num_postings);
        LOG(INFO) << "D-ZLIB-9 BPI = " << DBPI;
        
        auto lz_store_freqs = typename lz_store<coder::zlib<9>, factorization_blocksize>::builder{}
                            .set_rebuild(args.rebuild)
                            .set_threads(args.threads)
                            .build_or_load(col,col.freqs_file,"F-ZLIB-9");
        verify_index(col.freqs_file, lz_store_freqs);
        
        auto freqs_bytes = lz_store_freqs.size_in_bytes();
        auto freqs_bits = freqs_bytes * 8;
        LOG(INFO) << "F-ZLIB-9 bytes = " << freqs_bytes;
        double FBPI = freqs_bits / double(col.num_postings);
        LOG(INFO) << "F-ZLIB-9 BPI = " << FBPI;
    }
    */
    {
        auto lz_store_docs = typename lz_store<coder::zstd<9>, factorization_blocksize>::builder{}
                            .set_rebuild(args.rebuild)
                            .set_threads(args.threads)
                            .build_or_load(col,col.docs_file,"D-ZSTD-9");
        verify_index(col.docs_file, lz_store_docs);
        
        auto docs_bytes = lz_store_docs.size_in_bytes();
        auto docs_bits = docs_bytes * 8;
        LOG(INFO) << "D-ZSTD-9 bytes = " << docs_bytes;
        double DBPI = docs_bits / double(col.num_postings);
        LOG(INFO) << "D-ZSTD-9 BPI = " << DBPI;
        
        auto lz_store_freqs = typename lz_store<coder::zstd<9>, factorization_blocksize>::builder{}
                            .set_rebuild(args.rebuild)
                            .set_threads(args.threads)
                            .build_or_load(col,col.freqs_file,"F-ZSTD-9");
        verify_index(col.freqs_file, lz_store_freqs);
        
        auto freqs_bytes = lz_store_freqs.size_in_bytes();
        auto freqs_bits = freqs_bytes * 8;
        LOG(INFO) << "F-ZSTD-9 bytes = " << freqs_bytes;
        double FBPI = freqs_bits / double(col.num_postings);
        LOG(INFO) << "F-ZSTD-9 BPI = " << FBPI;
    }
    /*
    {
        auto lz_store_docs = typename lz_store<coder::lzma<6>, factorization_blocksize>::builder{}
                            .set_rebuild(args.rebuild)
                            .set_threads(args.threads)
                            .build_or_load(col,col.docs_file,"D-LZMA-9");
        verify_index(col.docs_file, lz_store_docs);
        
        auto docs_bytes = lz_store_docs.size_in_bytes();
        auto docs_bits = docs_bytes * 8;
        LOG(INFO) << "D-LZMA-9 bytes = " << docs_bytes;
        double DBPI = docs_bits / double(col.num_postings);
        LOG(INFO) << "D-LZMA-9 BPI = " << DBPI;
        
        auto lz_store_freqs = typename lz_store<coder::lzma<9>, factorization_blocksize>::builder{}
                            .set_rebuild(args.rebuild)
                            .set_threads(args.threads)
                            .build_or_load(col,col.freqs_file,"F-LZMA-9");
        verify_index(col.freqs_file, lz_store_freqs);
        
        auto freqs_bytes = lz_store_freqs.size_in_bytes();
        auto freqs_bits = freqs_bytes * 8;
        LOG(INFO) << "F-LZMA-9 bytes = " << freqs_bytes;
        double FBPI = freqs_bits / double(col.num_postings);
        LOG(INFO) << "F-LZMA-9 BPI = " << FBPI;
    }
    */
    
    return EXIT_SUCCESS;
}