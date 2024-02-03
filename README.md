# Turf Booking System

This C program implements a turf booking system for managing turf slots, bookings, and administration tasks. It provides functionality for admins to add, list, modify, and delete turf slots, calculate profits for specific days or months, while users can make bookings, search for available slots, and cancel bookings.

## Features

- **Admin Functions:**
  - Add turf slots
  - List turf slots
  - Modify turf slots
  - Delete turf slots
  - Calculate profits for a specific day or month

- **User Functions:**
  - Make bookings
  - Search for available slots
  - Cancel bookings

## Usage

1. Compile the program using a C compiler.
   ```bash
   gcc turf_booking_system.c -o turf_booking_system
   ```

2. Run the compiled executable.
   ```bash
   ./turf_booking_system
   ```

3. Follow the on-screen prompts to navigate through admin tasks, make bookings, search for slots, and cancel bookings.

## File Structure

- `turf_booking_system.c`: Main C program source code.
- `turf.dat`: File storing turf slot information.
- `booking.dat`: File storing booking information.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
