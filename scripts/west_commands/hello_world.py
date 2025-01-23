import os

# https://docs.zephyrproject.org/latest/develop/west/extensions.html
from west.commands import WestCommand

# west hello_world -m "Test message..." 
# west hello_world -c 
# west hello_world --mode manual 
# west hello_world --retries 10 
# west hello_world --coordinates 9 8
# west hello_world --names John Emily Ethan
class HelloWorld(WestCommand):
    def __init__(self):
        super().__init__(
            'hello_world', # command_name
            'Prints a custom greeting to the terminal', # help
            'Runs hello_world command for test purposes.' #description
        )

    def do_add_parser(self, parser_adder):
        parser = parser_adder.add_parser(
            self.name, help=self.help, description=self.description)
        
        # Add some example options using the standard argparse module API.
        # Provide a value for this argument when invoking the command.
        parser.add_argument('-m', '--message', 
                            default='Hello, World!',
                            #required=True,
                            help='Custom message to print')
        
        # When present, stores True in the check attribute. If not present, it defaults to False.
        parser.add_argument('-c', '--check', 
                            action='store_true', 
                            help='Check verbose status')

        # This limits the user to choosing either 'auto' or 'manual' for the --mode argument.
        parser.add_argument('--mode', 
                            choices=['auto', 'manual'], 
                            help='Select the operation mode')

        # This argument accepts an integer value and defaults to 3 if not specified. The value is stored as an integer.
        parser.add_argument('--retries', 
                            type=int, 
                            default=3, 
                            help='Set the number of retries')

        # This collects exactly two arguments from the command line and converts them into integers.
        parser.add_argument('--coordinates', nargs=2, type=int, help='Enter coordinates (x, y)')

        # This collects zero or more values into a list. If the option is not present, the names attribute will be an empty list.
        parser.add_argument('--names', nargs='*', help='List of names to process')

        return parser

    def do_run(self, args, unknown_args):
        print(args.message)
        print(args.check)
        print(args.mode)
        print(args.retries)
        print(args.coordinates)
        print(args.names)
