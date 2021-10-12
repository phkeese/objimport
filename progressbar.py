import sys

class ProgressBar:
	def __init__(self, message: str, maximum: int, width: int) -> None:
		self.message = message
		self.maximum = maximum
		self.width = max(10, width - len(message) - 6 - 1)
		self.value = 0
		self.set_value(0)
		
	def finish(self) -> None:
		self.set_value(self.maximum)
		print("")

	def set_value(self, value: int) -> None:
		self.value = value
		progress = float(self.value) / self.maximum
		bar = int(progress * self.width)
		no_bar = self.width - bar
		percent = int(100 * progress)
		print(f"\r{self.message} {'#' * bar}{' ' * no_bar} ({percent}%)", end='')
		sys.stdout.flush()
		
	
	def increment(self) -> None:
		self.set_value(self.value + 1)