# backend/main.py
from fastapi import FastAPI, UploadFile, File
from model import ImageClassifier
import shutil
import uuid
import os

app = FastAPI()
classifier = ImageClassifier()

UPLOAD_DIR = "uploads"
os.makedirs(UPLOAD_DIR, exist_ok=True)

@app.post("/classify/")
async def classify_image(file: UploadFile = File(...)):
    file_path = f"{UPLOAD_DIR}/{uuid.uuid4().hex}_{file.filename}"
    with open(file_path, "wb") as buffer:
        shutil.copyfileobj(file.file, buffer)

    label = classifier.predict(file_path)
    os.remove(file_path)
    return {"result": label}
