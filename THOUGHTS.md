# General Thoughts and Comments

***On File Writing:*** 

    this turned out to be the hardest part, mainly because C++ standard libraries are annoying.
    but also because i need to write bits while file writing is byte aligned.
    that means there's paddding that needs to be added to the end if our compressed file length is
    not byte aligned. which means we'll have to store the length of the compressed file to avoid
    having extra 0's added to our file. but to calculate the length can only be done after we
    wen't over the entire file. and the size should be in the header at the start. so either we go over the entire file in a buffer and keep the size and write only at the end (bad for really
    large files) or we don't use the size somehow which i can't figure out how. maybe the
    huffman code deals with it becase no code ends in just 0's? don't know. i'm tired :<

    I JUST THOUGHT OF SOMETHING: i know the histogram of each symbol and the dict gives me the length of the code. so it's just the sum of the frequency*code_length
