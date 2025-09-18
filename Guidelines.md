# The Mountain – Guidelines
Information held within dictates the terminology, naming, and code structure practices
to be followed for programs built inside the Mountain.

## Terminology

**Boudler** One of the things built inside of The Mountain. Typically corresponds to one
            target.

**Label**	One of the parts of a symbol's name. These are typically separated by
			underscores, though not everything separated by an underscore is a distinct
			label.
			
## Naming
Nearly every externally accessible symbol in every boudler must be prefixed with the 
name of the boulder it is from.

Exceptions include:
	- `struct` field names. These must be named like local variables
	- The Boulder "Lapidary". Its names are designed to be short, and conforming to this
		rule would defeat Lapidary's purpose.

### Capitalization
Each label in a type's name must use `UpperCamelCase`.
The lowest-label level in a function's name must be named using `lowerCamelCase`.
Local variables, function arguments, and `struct` field names must only contain
one label, which must use `snake_case`.

## Error Handling
In functions whose main output is given through a passed-in pointer, errors should be
reported via the return value. In these cases, the return value should be an `i32`,
with a returned `0` indicating success. Other return values can be used to indicate
errors. This pattern is used to emulate the behaviour of a `main()` function, something
every C programmer is familiar with.

Generally, a given error value should only be returned by one code path, so that
the value can be used to better understand what went wrong, to help with debugging.
