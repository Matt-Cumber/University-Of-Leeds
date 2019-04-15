from config import SQLALCHEMY_DATABASE_URI
from App import db
from App.models import User, Post, Profile
import os.path

db.create_all()
user1 = User(email="dummy@leeds.ac.uk",password="123")
user2 = User(email="testbot@leeds.ac.uk",password="123")
profile1 = Profile(pr_id=user1)
profile2 = Profile(pr_id=user2)
db.session.add(user1)
db.session.add(user2)
db.session.add(profile1)
db.session.add(profile2)
db.session.commit()
