# CV
2020년 2학기에 들은 컴퓨터비전 과제 및 프로젝트 소스코드입니다.

HW2_1는 HoG (histogram of oriented gradients) 특징 추출 (simplified version)를 LOWLEVEL로 구현 한 것입니다.
Magnitude는 gray scale 영상으로 도시.
Gradient는 0~359도의 방향에 따라 HSL 컬러공간에서로 표현하고 RGB로 변환.
Gradient 방향각도를 매 30도 단위로 양자화하여 히스토그램을 만들고 이를 12차원의 벡터로 표현한 후 정규화 (norm = 1) 하여 제시.
사람-사람, 사람-자동차 등 벡터의 거리를 이용한 매칭을 수행하고 HoG 특징이 물체 인식에 사용될 수 있는 유용한 특징임을 보인다.
(참고) Original HoG 특징 검출은 bounding box를 작은 블록으로 나누고 블록 내부에서 각각 histogram을 구하지만 본 과제는 bounding box 전체를 하나의 블록으로 본다. 따라서 original HoG와 같은 성능을 보이지는 않지만 유용성 검증은 가능함.

HW2_2는 Harris corner 검출을 LOWLEVEL로 구현 한 것입니다.
A. R 값의 영상 (문제1의 와 같이 gray scale 또는 color code로 표현)
B. Threshold 영상
C. NMS 수행한 최종 corner point 영상

HW3은 파노라마 LOWLEVEL로 구현 한 것입니다.

Termproject는 파이토치를 이용하여 코랩에서 새와 비행기를 구분하도록 만든 코드입니다.
