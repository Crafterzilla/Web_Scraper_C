import re

def count_word_occurrences(filename, word):
    with open(filename, 'r') as file:
        text = file.read().lower()  # Convert to lowercase for case-insensitive matching

        #pattern = rf'\b{word}\b|\B{word}\B'
        pattern = rf'(?={word})' 
        matches = re.findall(pattern, text, re.IGNORECASE)
        return len(matches)

        #rint(text[0:1000])
        print(text.split()[0:1000])
    return text.split().count(word.lower())  # Count occurrences

# Example usage
filename = "./output/test.html"
word = "Dog"
count = count_word_occurrences(filename, word)
print(f"The word '{word}' appears {count} times in {filename}.")


"""
Test Cases:
    //Word is surrounded by " "
    <p>The dog is playing</p>

    //Word is surrounded next to ">"
    //Divided by space
    <p>Dog is playing</p>

    //Word is in a url ">"
    //Divided by space
    <p>http://cool_dogs.com</p>

    //Word is followed by another char
    <p>Those are some cool dogs</p>
    
    //Word is not even readable by user
    //In this case, "dog-fact" is not readable by user
    <div class="dog-fact">Dogs have an incredible sense of smell, which is 40 times better than that of humans.</div>

    

"""

