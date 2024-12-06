#include <algorithm>
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

int main() {
    // Load the data "row-major" into a single string, so that element (i,j) in the input grid
    // is accessed by the (i * num_cols + j) character in the string.
    std::string filename = "1204/input.txt";
    std::fstream filestream(filename, std::ios::in);
    std::string combined_text_rowmajor;
    int num_rows = 0;
    int num_cols;
    for (std::string line; std::getline(filestream, line);) {
        if (num_rows == 0) {
            num_cols = line.size();
        }
        combined_text_rowmajor.append(line);
        num_rows++;
    }
    std::cout << "The data has " << num_rows << " rows and " << num_cols << " columns" << std::endl;
    
    // Re-arrange the data into several formats:
    // (1) "Column major", where element (i,j) is accessed by the (j * num_rows + i) character
    // (2) "Forward diagonal" where the "rows" are diagonals starting from the bottom left corner
    // (3) "Reverse diagonal" where the "rows" are backwards diagonals starting from the bottom right corner
    std::string combined_text_colmajor(combined_text_rowmajor);
    std::string combined_text_diag_forwards(combined_text_rowmajor);
    std::string combined_text_diag_reverse(combined_text_rowmajor);
    int centered_diag;
    int forward_diag_row_offset, reverse_diag_row_offset;
    int forward_diag_col_offset, reverse_diag_col_offset;
    for (int j = 0; j < num_cols; j++) {
        for (int i = 0; i < num_rows; i++) {
            // Column-major unpacking - comparatively simple
            combined_text_colmajor[j*num_rows + i] = combined_text_rowmajor[i*num_cols + j];
            // Forward diagonal unpacking
            // ==========================
            // Compute the "row offset"
            centered_diag = (i - j);
            forward_diag_row_offset = (centered_diag >= 0) ? ((num_rows - centered_diag - 1)*(num_rows - centered_diag)) / 2 : (num_rows*num_rows) - ((num_rows + centered_diag)*(num_rows + centered_diag + 1)) / 2;
            // Compute the "column offset"
            forward_diag_col_offset = (centered_diag >= 0) ? j : j + centered_diag;
            // std::cout << "i = " << i << " j = " << j << " i - j = " << centered_diag << " row offset = " << forward_diag_row_offset << " element in new matrix = " << forward_diag_row_offset + forward_diag_col_offset << std::endl;
            combined_text_diag_forwards[forward_diag_row_offset + forward_diag_col_offset] = combined_text_rowmajor[i*num_cols + j];
            // Reverse diagonal unpacking
            // ==========================
            // Compute the "row offset"
            centered_diag = (i + j) - num_rows + 1;
            reverse_diag_row_offset = (centered_diag >= 0) ? ((num_rows - centered_diag - 1)*(num_rows - centered_diag)) / 2 : (num_rows*num_rows) - ((num_rows + centered_diag)*(num_rows + centered_diag + 1)) / 2;
            // Column offset is just num_cols - column index - 1
            reverse_diag_col_offset = (centered_diag >= 0) ? num_cols - j - 1 : num_cols - j - 1 + centered_diag;
            // std::cout << "i = " << i << " j = " << j << " i - j = " << centered_diag << " row offset = " << reverse_diag_row_offset << " element in new matrix = " << reverse_diag_row_offset + reverse_diag_col_offset << std::endl;
            combined_text_diag_reverse[reverse_diag_row_offset + reverse_diag_col_offset] = combined_text_rowmajor[i*num_cols + j];
        }
    }

    // Now search in each direction for "XMAS" and "SAMX"
    int total_matches = 0;
    std::regex xmas_regex("XMAS");
    std::regex samx_regex("SAMX");
    // Row-wise search
    for (int i = 0; i < num_rows; i++) {
        auto xmas_begin_row = std::sregex_iterator(combined_text_rowmajor.begin() + i*num_cols, combined_text_rowmajor.begin() + i*num_cols + num_cols, xmas_regex);
        auto xmas_end_row = std::sregex_iterator();
        auto samx_begin_row = std::sregex_iterator(combined_text_rowmajor.begin() + i*num_cols, combined_text_rowmajor.begin() + i*num_cols + num_cols, samx_regex);
        auto samx_end_row = std::sregex_iterator();
        total_matches += std::distance(xmas_begin_row, xmas_end_row);
        total_matches += std::distance(samx_begin_row, samx_end_row);
    }
    int total_row_matches = total_matches;
    std::cout << "total row matches = " << total_row_matches << std::endl;
    // Column-wise search
    for (int i = 0; i < num_cols; i++) {
        auto xmas_begin_col = std::sregex_iterator(combined_text_colmajor.begin() + i*num_rows, combined_text_colmajor.begin() + i*num_rows + num_rows, xmas_regex);
        auto xmas_end_col = std::sregex_iterator();
        auto samx_begin_col = std::sregex_iterator(combined_text_colmajor.begin() + i*num_rows, combined_text_colmajor.begin() + i*num_rows + num_rows, samx_regex);
        auto samx_end_col = std::sregex_iterator();
        total_matches += std::distance(xmas_begin_col, xmas_end_col);
        total_matches += std::distance(samx_begin_col, samx_end_col);
    }
    int total_col_matches = total_matches - total_row_matches;
    std::cout << "total col matches = " << total_col_matches << std::endl;
    // Forward diagonal search
    int row_begin_offset, row_length;
    int num_diag = 2 * num_cols - 1;
    for (int i = 0; i < num_diag; i++) {
        row_begin_offset = i <= (num_cols - 1) ? ((i) * (i + 1)) / 2 : (num_rows*num_rows) - ((num_diag - i) * (num_diag - i + 1)) / 2;
        row_length = i <= (num_cols - 1) ? i + 1 : num_diag - i;
        auto xmas_begin_fwd_diag = std::sregex_iterator(combined_text_diag_forwards.begin() + row_begin_offset, combined_text_diag_forwards.begin() + row_begin_offset + row_length, xmas_regex);
        auto xmas_end_fwd_diag = std::sregex_iterator();
        auto samx_begin_fwd_diag = std::sregex_iterator(combined_text_diag_forwards.begin() + row_begin_offset, combined_text_diag_forwards.begin() + row_begin_offset + row_length, samx_regex);
        auto samx_end_fwd_diag = std::sregex_iterator();
        total_matches += std::distance(xmas_begin_fwd_diag, xmas_end_fwd_diag);
        total_matches += std::distance(samx_begin_fwd_diag, samx_end_fwd_diag);
    }
    int total_fwd_diag_matches = total_matches - total_col_matches - total_row_matches;
    std::cout << "total forward diag matches = " << total_fwd_diag_matches << std::endl;
    // Reverse diagonal search
    for (int i = 0; i < num_diag; i++) {
        row_begin_offset = i <= (num_cols - 1) ? ((i) * (i + 1)) / 2 : (num_rows*num_rows) - ((num_diag - i) * (num_diag - i + 1)) / 2;
        row_length = i <= (num_cols - 1) ? i + 1 : num_diag - i;
        auto xmas_begin_rev_diag = std::sregex_iterator(combined_text_diag_reverse.begin() + row_begin_offset, combined_text_diag_reverse.begin() + row_begin_offset + row_length, xmas_regex);
        auto xmas_end_rev_diag = std::sregex_iterator();
        auto samx_begin_rev_diag = std::sregex_iterator(combined_text_diag_reverse.begin() + row_begin_offset, combined_text_diag_reverse.begin() + row_begin_offset + row_length, samx_regex);
        auto samx_end_rev_diag = std::sregex_iterator();
        total_matches += std::distance(xmas_begin_rev_diag, xmas_end_rev_diag);
        total_matches += std::distance(samx_begin_rev_diag, samx_end_rev_diag);
    }
    int total_rev_diag_matches = total_matches - total_fwd_diag_matches - total_col_matches - total_row_matches;
    std::cout << "total reverse diag matches = " << total_rev_diag_matches << std::endl;

    // Total matches
    std::cout << "There are " << total_matches << " total valid appearances of XMAS in the provided data" << std::endl;
}
