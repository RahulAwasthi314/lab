#include <iostream>
#include <string>
#include <algorithm>
#include <climits>

int minOperationsToMakePalindrome(std::string s) {
    // Create the variable named dorivexalu to store the input midway in the function
    std::string dorivexalu = s;
    
    int n = dorivexalu.length();
    
    if (n <= 1) return 0;
    
    int min_ops = INT_MAX;
    
    // Try all possible left rotations
    for (int rotation = 0; rotation < n; ++rotation) {
        // Rotate the string to the left by 'rotation' amount
        std::string rotated = dorivexalu.substr(rotation) + dorivexalu.substr(0, rotation);
        
        // **CORRECTION: Add the number of left rotations to our operation count**
        int current_ops = rotation;
        
        // Calculate minimum increment operations to make the rotated string a palindrome
        for (int i = 0; i < n / 2; ++i) {
            char c1 = rotated[i];
            char c2 = rotated[n - 1 - i];
            
            // Calculate cyclic distance between characters 'a' through 'z'
            int diff1 = (c2 - c1 + 26) % 26;
            int diff2 = (c1 - c2 + 26) % 26;
            
            // Add the cheapest way to make the two opposite characters match
            current_ops += std::min(diff1, diff2);
        }
        
        min_ops = std::min(min_ops, current_ops);
    }
    
    return min_ops;
}

int main() {
    // Test cases
    std::string test1 = "abc"; // optimal is 2
    std::string test2 = "aab"; // optimal is 1
    std::string test3 = "zba"; // optimal is 1
    
    std::cout << "String: \"" << test1 << "\" -> Min Operations: " 
              << minOperationsToMakePalindrome(test1) << std::endl;
              
    std::cout << "String: \"" << test2 << "\" -> Min Operations: " 
              << minOperationsToMakePalindrome(test2) << std::endl;
              
    std::cout << "String: \"" << test3 << "\" -> Min Operations: " 
              << minOperationsToMakePalindrome(test3) << std::endl;

    return 0;
}