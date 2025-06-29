# backend/model.py
import torch
import torchvision.transforms as transforms
from torchvision import models
from PIL import Image

class ImageClassifier:
    def __init__(self):
        self.model = models.mobilenet_v2(pretrained=True)
        self.model.eval()
        self.transform = transforms.Compose([
            transforms.Resize(256),
            transforms.CenterCrop(224),
            transforms.ToTensor(),
            transforms.Normalize(
                mean=[0.485, 0.456, 0.406],
                std=[0.229, 0.224, 0.225]
            )
        ])

        with open("imagenet_classes.txt") as f:
            self.labels = [line.strip() for line in f.readlines()]

    def predict(self, image_path):
        img = Image.open(image_path).convert("RGB")
        img_tensor = self.transform(img).unsqueeze(0)  # [1, 3, 224, 224]
        with torch.no_grad():
            outputs = self.model(img_tensor)
        _, predicted = outputs.max(1)
        return self.labels[predicted.item()]
