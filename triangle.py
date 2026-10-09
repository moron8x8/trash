import math

class GeometryLog:
  __instance = None


  def __new__(cls, *args, **kwargs):
    if cls.__instance is None:
      cls.__instance = super().__new__(cls)
      cls.__instance.records = []
    return cls.__instance

  def add(self, triangle: "Triangle") -> None:
    self.records.append(f"#{triangle.id}: {triangle.a}, {triangle.b}, {triangle.c}")
    
  def history(self) -> list[str]:
    return self.records.copy()

class PositiveNumber:
  def __set_name__(self, owner: type, name: str) -> None:
    self.name = "_" + name 

  def __get__(self, instance, owner: type):
    if instance is None:
      return self
    return getattr(instance, self.name)

  def __set__(self, instance, value) -> None:
    if type(value) is not int:
      raise TypeError("side must be int")
    if value <= 0:
      raise ValueError("side must be positive")
    setattr(instance, self.name, value)


class Triangle:
  """Triangle with integer sides."""
  count = 0
  a = PositiveNumber()
  b = PositiveNumber()
  c = PositiveNumber()


  def __init__(self, a: int, b: int, c: int) -> None:
    self.a = a
    self.b = b
    self.c = c
    if not self.is_valid_triangle(a, b, c):
      raise ValueError("triangle with these sides does not exist")
    Triangle.count += 1
    self.__id = Triangle.count
    GeometryLog().add(self)


  def __setattr__(self, name: str, value: object) -> None:
    if name in ("a", "b", "c") and all(hasattr(self, "_" + s) for s in "abc"):
      sides = {"a": self.a, "b": self.b, "c": self.c}
      sides[name] = value
      if not self.is_valid_triangle(*sides.values()):
        raise ValueError("triangle with these sides does not exist")
    super().__setattr__(name, value)

  def __delattr__(self, name: str) -> None:
    raise AttributeError("attributes can't be deleted")


  @property
  def id(self) -> int:
    return self.__id

  @property
  def perimeter(self) -> int:
    return self.a + self.b + self.c

  @property
  def area(self) -> float:
    p = self.perimeter / 2
    return (p * (p - self.a) * (p - self.b) * (p - self.c)) ** 0.5

  @property
  def kind(self) -> str:
    n = len({self.a, self.b, self.c})
    return {1: "equilateral", 2: "isosceles", 3: "scalene"}[n]

  @property
  def is_right(self) -> bool:
    arr = sorted([self.a, self.b, self.c])
    return arr[2] ** 2 == arr[1] ** 2 + arr[0] ** 2

  @property
  def angles(self) -> tuple[float, float, float]:
    a, b, c = self.a, self.b, self.c

    def angle(opposite: int, s1: int, s2: int) -> float:
      cos = (s1 ** 2 + s2 ** 2 - opposite ** 2) / (2 * s1 * s2)
      return round(math.degrees(math.acos(cos)), 2)

    return angle(a, b, c), angle(b, a, c), angle(c, a, b)

  @classmethod
  def equilateral(cls, side: int) -> "Triangle":
    return cls(side, side, side) 

  @staticmethod
  def is_valid_triangle(a: int, b: int, c: int) -> bool:
    return (max((a, b, c)) < (sum((a, b, c)) - max((a, b, c))))
