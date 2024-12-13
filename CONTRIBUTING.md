# How to contribute 🫦🫀🫂
<b>You just made my day.</b> This is my reaction: 😊

**Big important note:**
Those are just my preferences. You can always suggest something else or just do it your way. Different perspectives are always welcome

Fork this repository, make your changes, and submit a pull request. I'll be more than happy to review it

No need to follow any standardized format. I'll take care of the rest


#
## Dependencies and Libraries 🍌
Not fully decided yet. As in now, Windows and g++14 or above.
<details>
<summary><i>Rules and Guidelines</i></summary>
Don't go crazy with the non-stl libraries. I have ~int(~int(0)) idea how to use cmake or any other build tools. If you have a reason to actually include something, let me know.
</details>

#
## C++ Source Code 😵‍💫
Only because a feature exists, doesn't mean it should be used. Here are some guidelines to follow when writing C++ code for this project.

#### Usage of features
<details>
<summary><i>C++ Built-in</i></summary>
<ul>
    <li> Leave the flushing of the buffer to the program and OS (no std::endl)
        <ul>
            <li> Use '\n' instead
            <li> Use std::flush when necessary
        </ul>
    <li> Avoid inheritance when possible
        <ul>
            <li> Except for interfaces and abstract classes
        </ul>
    <li> Encapsulation is overrated. Everything should be public
    <li> Use the auto keyword only if it makes the code more readable
    <li> Creating a method instead of static function is recommended
    <li> Use length() instead of size() for strings
    <li> Whatever you do, stay away from C
</ul>
</details>
<details>
<summary><i>Dynamic allocation</i></summary>
Stay away from any kind of dynamic allocation. Not even smart pointers. Trust the stl containers to do the job for you. <b>Use the damn stack</b>
</details>


#### Syntax
<details>
<summary><i>Naming conventions</i></summary>
<ul>
    <li>Classes, Enums, Structs: PascalCase
    <li>Functions, Methods: snake_case
    <li>Variables: camelCase
    <li>Constants: UPPERCASE_SNAKE_CASE
    <li>Others: Crazy_Case
</ul>
</details>

<details>
<summary><i>Defining stuff</i></summary>
<ul>
    <li>Use structs like how you would in C
    <li>Functions shouldn't have default parameters
    <li>"using namespace std" isn't allowed. (polluting the global namespace)
    <li>Use constexpr wherever possible
</ul>
</details>

<details>
<summary><i>Others</i></summary>
<ul>
    <li>"or" instead of "||"
    <li>"and" instead of "&&"

</ul>
</details>



<details>
<summary><i>Banned keywords</i></summary>
<ul>
    <li>const_case (breaks the very idea of using const. Really unsafe)
    <li>Union (Unpredictable and unnecessary most of the time)
    <li>goto (Spaghetti code)
    <li>No idea what they do:
        <ul>
            <li>volatile
            <li>mutable
            <li>extern
            <li>thread_local
            <li>alignas
            <li>alignof
            <li>decltype
            <li>typeid
        </ul>
</ul>
</details>