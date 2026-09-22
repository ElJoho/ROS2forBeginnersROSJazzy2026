// ============================================================================
// my_first_node.cpp
// The exact same minimal ROS 2 C++ node from the lesson — now with a
// line-by-line explanation of both the ROS 2 parts and the underlying C++
// syntax (pointers, templates, namespaces, macros, etc.).
// ============================================================================

// "#include" tells the compiler to paste in the declarations from another
// file before compiling this one, so it knows what things like rclcpp::init
// or rclcpp::Node actually are.
// "rclcpp/rclcpp.hpp" is the "umbrella" header for rclcpp — the C++ ROS 2
// client library ("rcl" = ROS Client Library, "cpp" = for C++). Including it
// pulls in everything needed to create nodes, log messages, and communicate
// over ROS 2 — the same role `import rclpy` plays on the Python side.
#include "rclcpp/rclcpp.hpp"

// Every C++ program begins running in main(). Its two parameters are how the
// operating system hands your program whatever was typed after the
// program's name on the command line:
//   - argc ("argument count"): how many command-line arguments were given.
//     Always at least 1, because the program's own name counts as the
//     first one.
//   - argv ("argument vector"): the arguments themselves, stored as an
//     array of C-style strings. argv[0] is the program's name, argv[1] is
//     the first real argument, and so on.
//   - The type `char **argv` reads as "a pointer to a pointer to char" —
//     the classic C/C++ way to represent "an array of strings" as a
//     function parameter (a string is itself just a pointer to its first
//     character, so an array of strings is a pointer to pointers).
// ROS 2 needs argc/argv passed into rclcpp::init() below so it can pull out
// any special ROS command-line arguments (e.g. renaming a node at launch)
// before the rest of your code runs.
int main(int argc, char **argv){

	// rclcpp::init() must be the FIRST ROS 2 call in any node — it starts
	// up ROS 2's communication layer underneath your program, so that
	// creating nodes afterward actually works.
	//
	// About the "::" here (and everywhere else in this file): it's C++'s
	// SCOPE RESOLUTION OPERATOR. "rclcpp" is a namespace — a named
	// container that groups related functions/classes together so their
	// names don't clash with identically-named things from other
	// libraries. Writing rclcpp::init says "use the init function that
	// specifically lives inside the rclcpp namespace" — conceptually the
	// same job a file path like folder/file.txt does: it points at one
	// exact file instead of any file named file.txt anywhere on disk.
	//
	// argc and argv are passed straight through so ROS 2 can read its own
	// arguments, as explained above.
	rclcpp::init(argc,argv);

	// This line creates the node itself, and it packs in several distinct
	// C++ ideas at once:
	//
	// - "auto": tells the compiler to work out this variable's type by
	//   itself from whatever is on the right of the "=", instead of you
	//   spelling it out by hand. It saves writing out the full (long)
	//   pointer type yourself.
	//
	// - "std::make_shared<rclcpp::Node>(...)": std:: means this function
	//   comes from the C++ Standard Library's namespace — the same "::"
	//   as above. make_shared does two things in one step: it allocates
	//   memory for a new object, and wraps it in a "shared pointer"
	//   (std::shared_ptr) — a smart pointer that automatically frees that
	//   memory once nothing needs it anymore. You never call delete on it
	//   yourself, unlike a raw C++ pointer.
	//
	// - The "<rclcpp::Node>" part is a TEMPLATE ARGUMENT, in angle
	//   brackets. make_shared is written generically (a "template
	//   function") so it can build a shared pointer to ANY type — an int,
	//   your own class, or here, an rclcpp::Node. The compiler has no way
	//   to guess which type you want built; the <...> is how you tell it
	//   explicitly. Without it, this line wouldn't compile — make_shared()
	//   alone doesn't say *what* to make shared.
	//
	// - "(\"cpp_test\")" is the argument passed to the Node's own
	//   constructor once it's created — this is the NODE NAME, the name
	//   that shows up in logs and in ROS 2 command-line tools.
	//
	// Put together: create a new rclcpp::Node named "cpp_test", wrap it in
	// a shared pointer, and let the compiler infer that `node`'s type is
	// "a shared pointer to an rclcpp::Node." Note that `node` is NOT the
	// Node object itself — it's a smart pointer that *points to* it.
	auto node = std::make_shared<rclcpp::Node>("cpp_test");

	// This prints a log message to the terminal.
	//
	// RCLCPP_INFO is written in all caps because it's a MACRO, not a
	// regular function (all-caps is the C++ convention for macros). At
	// compile time it expands into extra code that attaches a timestamp,
	// the node's name, and an "INFO" severity level before printing the
	// message — you get all of that for free just by calling it this way.
	//
	// "node->get_logger()":
	//   - `node` is a pointer (from the line above) — it points to the
	//     Node object rather than being that object itself.
	//   - In C++, "." (dot) accesses a member of an object you hold
	//     directly; "->" (arrow) accesses a member through a pointer to
	//     that object. Since `node` is a pointer, node->get_logger() means
	//     "go to the Node object that `node` points to, and call its
	//     get_logger() function." Writing node.get_logger() instead would
	//     fail to compile — "." would try to call get_logger() on the
	//     shared_ptr wrapper itself, which has no such function; only the
	//     Node object it points to does.
	//   - get_logger() returns this node's own logger, which already knows
	//     the node's name, so every message is correctly tagged
	//     "[cpp_test]" automatically.
	//
	// The second argument, "Hello World", is just the text being logged.
	RCLCPP_INFO(node->get_logger(), "Hello World");

	// rclcpp::spin() hands control over to ROS 2 and keeps this node alive
	// — listening for incoming messages, timers, service calls, etc. —
	// until it's told to stop (normally by pressing Ctrl+C). Without this
	// line, the program would fall straight through to shutdown() and exit
	// immediately after the log line above.
	// It's given `node` (the shared pointer) as its argument so ROS 2
	// knows exactly which node's activity it's responsible for keeping
	// alive.
	rclcpp::spin(node);

	// Once spin() returns — meaning the node has been told to stop —
	// rclcpp::shutdown() cleanly shuts ROS 2 back down. This should always
	// be the LAST ROS 2 call in a node, mirroring rclcpp::init() at the
	// top.
	rclcpp::shutdown();

	// main() must return an int to the operating system. 0 is the standard
	// way of saying "the program finished successfully"; any other value
	// would signal that something went wrong.
	return 0;
}
