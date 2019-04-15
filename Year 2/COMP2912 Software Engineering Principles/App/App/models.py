from datetime import datetime
from App import db, login_manager
from flask_login import UserMixin

#
@login_manager.user_loader
def load_user(user_id):
	return User.query.get(int(user_id))

#User model
class User(db.Model, UserMixin):
	id = db.Column(db.Integer, primary_key=True)
	email = db.Column(db.String(120), unique=True, nullable=False)
	password = db.Column(db.String(60), nullable=False)
	pr_id = db.relationship('Profile', backref='pr_id', lazy=True)

	def __repr__(self):
		return f"User('{self.email}')"



class Profile(db.Model):
	id = db.Column(db.Integer, primary_key=True)
	email = db.Column(db.String(120), db.ForeignKey('user.id'), unique=True, nullable=False)
	tiredness = db.Column(db.Integer, default=1, nullable=False)
	stress = db.Column(db.Integer, default=1, nullable=False)

	def __repr__(self):
		return f"Profile('{self.email}','{self.tiredness}','{self.stress}')"



#Post model
class Post(db.Model):
	id = db.Column(db.Integer, primary_key=True)
	title = db.Column(db.String(100), nullable=False)
	date = db.Column(db.DateTime, nullable=False, default=datetime.utcnow)
	content = db.Column(db.Text, nullable=False)
	user_id = db.Column(db.Integer, db.ForeignKey('user.id'), nullable=False)


	def __repr__(self):
		return f"Post('{self.title}','{self.date}')"
